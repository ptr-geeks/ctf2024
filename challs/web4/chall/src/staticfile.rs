use std::env::current_dir;
use actix_web::{Responder};
use actix_files::NamedFile;

pub async fn get_static_file(path: String, subfolder: String) -> impl Responder {
    let dir = current_dir().unwrap().join(subfolder);
    let path = dir.join(path).canonicalize()?;
    if !path.to_str().unwrap().starts_with(&dir.to_str().unwrap()) {
        return Err(std::io::Error::new(std::io::ErrorKind::Other, "Invalid path"));
    }

    let file = NamedFile::open(path);
    match file {
        Ok(file) => Ok(file),
        Err(e) => {
            println!("Error: {:?}", e);
            Err(std::io::Error::new(std::io::ErrorKind::Other, "Invalid path"))
        }
    }
}

