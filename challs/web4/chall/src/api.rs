use actix_web::{error, get, post, web, Error as ActixError, HttpRequest, HttpResponse, Result};
use serde::{Serialize, Deserialize};

use crate::db;

#[derive(Debug,Serialize,Deserialize)]
pub struct ImageShort {
    pub id: i32,
    pub name: String,
}

#[derive(Debug,Serialize,Deserialize)]
pub struct Image {
    pub id: i32,
    pub name: String,
    pub description: String,
    pub url: String,
}

#[derive(Debug,Serialize,Deserialize)]
pub struct ImageInsert {
    pub name: String,
    pub description: String,
    pub hash: String,
}

#[get("/api/images")]
pub async fn images(db: web::Data<db::Pool>) -> Result<HttpResponse, ActixError> {
    let pool = db.clone();
    let conn = web::block(move || pool.get())
        .await?
        .map_err(error::ErrorInternalServerError)?;

    let result = db::get_all_images(&conn).await;
    match result {
        Ok(images) => Ok(HttpResponse::Ok().json(images.into_iter().map(|image| ImageShort {
            id: image.id,
            name: image.name,
        }).collect::<Vec<ImageShort>>())),
        Err(err) => {
            println!("Error: {:?}", err);
            Ok(HttpResponse::InternalServerError().finish())
        }
    }
}

#[get("/api/images/{id}")]
pub async fn image_by_id(id: actix_web::web::Path<i32>, db: web::Data<db::Pool>) -> Result<HttpResponse, ActixError> {
    let pool = db.clone();
    let conn = web::block(move || pool.get())
        .await?
        .map_err(error::ErrorInternalServerError)?;

    let result = db::get_image_by_id(&conn, id.into_inner()).await;
    match result {
        Ok(image) => {
            match image {
                Some(image) => Ok(HttpResponse::Ok().json(Image {
                    id: image.id,
                    name: image.name,
                    description: image.description,
                    url: format!("/data/{}", image.hash),
                })),
                None => Ok(HttpResponse::NotFound().finish())
            }
        },
        Err(err) => {
            println!("Error: {:?}", err);
            Ok(HttpResponse::InternalServerError().finish())
        }
    }

}

#[post("/api/images")]
pub async fn insert_image_entry(
    req: HttpRequest,
    image: web::Json<ImageInsert>,
    db: web::Data<db::Pool>,
    secrets: web::Data<crate::Secrets>,
) -> Result<HttpResponse, ActixError> {
    match req.headers().get("x-api-key") {
        Some(key) => {
            if key != &secrets.apikey {
                return Ok(HttpResponse::Unauthorized().finish());
            }
        },
        None => {
            return Ok(HttpResponse::Unauthorized().finish());
        }
    }

    let pool = db.clone();
    let conn = web::block(move || pool.get())
        .await?
        .map_err(error::ErrorInternalServerError)?;

    let img = db::Image {
        id: 0,
        name: image.name.clone(),
        description: image.description.clone(),
        hash: image.hash.clone(),
    };
    let result = db::insert_image(&conn, img).await;
    match result {
        Ok(_) => Ok(HttpResponse::Ok().finish()),
        Err(err) => {
            println!("Error: {:?}", err);
            Ok(HttpResponse::InternalServerError().finish())
        }
    }
}
