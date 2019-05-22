use std::io;
use std::io::prelude::*;
use std::io::SeekFrom;
use std::fs::File;

fn main() {
    println!("Hello, world!");

    let modName = ask_user_module_name();

    let header_contents = read_module_header();
    let header_replaced = header_contents.replace("<--MODULE_NAME-->", &modName);

    let source_contents = read_module_source();
    let source_replaced = source_contents.replace("<--MODULE_NAME-->", &modName);

    save_module_header(&modName, header_replaced);
    save_module_source(&modName, source_replaced);
}

fn ask_user_module_name() -> String {
    return std::string::String::from("Stuff");
}

fn read_module_header() -> String {
    let mut contents = std::string::String::new();

    std::fs::File::open("templates/module.h.txt").unwrap().read_to_string(&mut contents);
    //return std::string::String::new();

    return contents;
}

fn read_module_source() -> String {
    return std::string::String::new();
}

fn save_module_header(moduleName: &str, contents: String) {
    std::fs::write(moduleName, contents);
}

fn save_module_source(moduleName: &str, contents: String) {

}