use actix_web::{get, App, HttpServer, Responder, web::{Data, Redirect}};
use r2d2_sqlite::SqliteConnectionManager;

mod db;
mod api;
mod staticfile;

#[derive(Clone)]
pub struct Secrets {
    pub apikey: String,
}

#[get("/")]
async fn index() -> impl Responder {
    Redirect::to("/index.html")
}

#[get("/{slug:.*\\.html}")]
async fn frontend(slug: actix_web::web::Path<String>) -> impl Responder {
    let file = slug.to_string();
    staticfile::get_static_file(file, "static".to_string()).await
}

#[get("/data/{slug:.*}")]
async fn files(slug: actix_web::web::Path<String>) -> impl Responder {
    let file = slug.to_string();
    staticfile::get_static_file(file, "data".to_string()).await
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    let manager = SqliteConnectionManager::file("database.sqlite3");
    let pool = db::Pool::new(manager).expect("Failed to create pool");

    let secrets = Secrets {
        apikey: std::env::var("API_KEY").expect("API_KEY must be set"),
    };

    HttpServer::new(move || App::new()
        .app_data(Data::new(secrets.clone()))
        .app_data(Data::new(pool.clone()))
        .service(api::image_by_id)
        .service(api::images)
        .service(api::insert_image_entry)
        .service(index)
        .service(files)
        .service(frontend)
    )
    .bind("0.0.0.0:8000")?
    .workers(4)
    .run()
    .await
}
