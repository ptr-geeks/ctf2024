use serde::{Serialize, Deserialize};

pub type Pool = r2d2::Pool<r2d2_sqlite::SqliteConnectionManager>;
pub type Connection = r2d2::PooledConnection<r2d2_sqlite::SqliteConnectionManager>;
type ImagesAggResult = Result<Vec<Image>, rusqlite::Error>;
type ImageAggResult = Result<Option<Image>, rusqlite::Error>;

#[derive(Debug,Serialize,Deserialize)]
pub struct Image {
    pub id: i32,
    pub name: String,
    pub description: String,
    pub hash: String,
}

impl Image {
    pub fn from_row(row: &rusqlite::Row) -> rusqlite::Result<Image> {
        Ok(Image {
            id: row.get(0)?,
            name: row.get(1)?,
            description: row.get(2)?,
            hash: row.get(3)?,
        })
    }
}

pub async fn get_image_by_id(conn: &Connection, id: i32) -> ImageAggResult {
    let mut stmt = conn.prepare("SELECT * FROM images WHERE id = ? AND NOT hidden")?;
    let mut rows = stmt.query(&[&id])?;
    if let Some(row) = rows.next()? {
        let image = Image::from_row(&row)?;
        Ok(Some(image))
    } else {
        Ok(None)
    }
}

pub async fn get_all_images(conn: &Connection) -> ImagesAggResult {
    let mut stmt = conn.prepare("SELECT * FROM images WHERE NOT hidden")?;
    let mut rows = stmt.query([])?;
    let mut images = Vec::new();
    while let Some(row) = rows.next()? {
        images.push(Image::from_row(&row)?);
    }
    Ok(images)
}

pub async fn insert_image(conn: &Connection, image: Image) -> rusqlite::Result<()> {
    conn.execute(
        "INSERT INTO images (name, description, hash, hidden) VALUES (?1, ?2, ?3, false)",
        &[&image.name, &image.description, &image.hash],
    )?;
    Ok(())
}
