use std::io::prelude::*;

fn main() {
    let scaffold_choice = ask_user_scaffold_choice();

    if scaffold_choice.is_some() && scaffold_choice.unwrap() == "module" {
        let mod_name_input = ask_user_module_name();
        let mod_name = mod_name_input.trim();

        let header_contents = read_module_header();
        let header_replaced = header_contents.replace("<--MODULE_NAME-->", mod_name);

        let source_contents = read_module_source();
        let source_replaced = source_contents.replace("<--MODULE_NAME-->", mod_name);

        save_module_header(mod_name, header_replaced);
        save_module_source(mod_name, source_replaced);
    }
    else {
        println!("Scaffold choice not recognized.");
    }
}

fn ask_user_scaffold_choice() -> Option<String> {
    println!("What kind of object do you want to scaffold");
    println!("Choices :");
    println!("  module");
    println!("");

    let mut user_input = std::string::String::new();

    let res = std::io::stdin().read_line(&mut user_input);

    user_input = user_input.trim().to_string();

    if res.is_err() {
        return None
    }

    match user_input.as_ref() {
        "module" => return Some(user_input),
        _ => return None
    }
}

fn ask_user_module_name() -> String {
    println!("Choose a module name : ");

    let mut user_input = std::string::String::new();

    let result = std::io::stdin().read_line(&mut user_input);

    if result.is_err()
    {
        return std::string::String::from("");
    }

    return user_input;
}

fn read_module_header() -> String {
    let mut contents = std::string::String::new();

    let result = std::fs::File::open("templates/module.h.txt").unwrap().read_to_string(&mut contents);

    if result.is_err()
    {
        return std::string::String::from("");
    }

    return contents;
}

fn read_module_source() -> String {
    let mut contents = std::string::String::new();

    let result = std::fs::File::open("templates/module.cpp.txt").unwrap().read_to_string(&mut contents);

    if result.is_err()
    {
        return std::string::String::from("");
    }

    return contents;
}

fn save_module_header(module_name: &str, contents: String) {
    let header_filename = std::string::String::from(module_name) + ".h";

    let _result = std::fs::write(header_filename, contents);
}

fn save_module_source(module_name: &str, contents: String) {
    let source_filename = std::string::String::from(module_name) + ".cpp";

    let _result = std::fs::write(source_filename, contents);
}
