use std::collections::HashMap;

fn main() {
    let mut args = std::env::args().skip(1);

    let arg = args.next().expect("No arguments passed to program.");
    let mut database = Database::new("sample_rust.db").expect("Could not read database");

    if arg == "set" {
        let key = args.next().unwrap();
        let value = args.next().unwrap();
        println!("Added new entry: The key is '{}' and the value is '{}'", key, value);

        database.insert(key, value);
        database.save("sample_rust.db").expect("Database was unable to save.")

    }

    if arg == "get" {
        let key = args.next().unwrap();
        let value = database.get(&key);
        println!("the value of '{}' is '{}'", key, value);
    }

}

struct Database {
    map: HashMap<String, String>
}

impl Database {
    fn new (path: &str) -> Result<Database, std::io::Error> {
        let contents = match std::fs::read_to_string(&path) {
            Ok(string) => {
                string
            }
            Err(error) => {
                if error.kind() == std::io::ErrorKind::NotFound {
                    std::fs::write(&path, "")?;
                    String::new()
                } else {
                    print!("{}",error);
                    return Err(error)
                }
            }
        };

        let mut map = HashMap::new();

        for line in contents.lines() {
            let chunks = line.split_once('\t').unwrap();
            let key = chunks.0;
            let value = chunks.1;
            map.insert(key.to_owned(), value.to_string());
        }

        Ok(Database { map })
    }

    fn insert(&mut self, key: String, value: String) {
        self.map.insert(key.to_uppercase(), value.clone());
        self.map.insert(key.to_owned(), value.to_owned());
    }

    fn get(&self, key: &str) -> &str {
        self.map.get(key).expect("No result found for this key")
    }

    fn save(&self, path: &str) -> Result<(), std::io::Error>  {
        let mut s = String::new();
        for (key, value) in &self.map {
            s += &format!("{}\t{}\n", key, value);
        }

        std::fs::write(path, s)
    }
}