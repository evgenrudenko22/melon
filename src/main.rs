use crossterm::{ExecutableCommand, terminal::{self, ClearType}, event::{self, KeyCode, KeyModifiers}, cursor};
use std::io::{stdout, Write};

fn main() {
    /*
    println!("\n\
    ##########\n\
    .........\n\
    ..;%%%;..\n\
    .;%@@@%;.\n\
    .;%%@%%;.\n\
    .;%%@%%;.\n\
    ..'%%%'..\n\
    .........\n\
    #########");
     */
    let mut stdout = stdout();
    stdout.execute(terminal::EnterAlternateScreen).unwrap();
    stdout.execute(terminal::Clear(ClearType::All)).unwrap();
    terminal::enable_raw_mode().unwrap();

    let mut text = String::new();

    loop {
        if event::poll(std::time::Duration::from_millis(500)).unwrap() {
            if let event::Event::Key(key) = event::read().unwrap() {
                match key.code {
                    // Quit from editor
                    KeyCode::Char('q') if key.modifiers.contains(KeyModifiers::CONTROL) => {
                        break;
                    },
                    // Handle backspace
                    KeyCode::Backspace => {
                        if !text.is_empty() {
                            text.pop();
                            stdout.execute(cursor::MoveLeft(1)).unwrap();
                            stdout.execute(terminal::Clear(ClearType::FromCursorDown)).unwrap();
                        }
                    }
                    KeyCode::Char(c) => {
                        text.push(c);
                        print!("{}", c);
                    },
                    _ => {}
                }

                stdout.flush().unwrap();
            }
        }
    }

    terminal::disable_raw_mode().unwrap();
    stdout.execute(terminal::LeaveAlternateScreen).unwrap();
}
