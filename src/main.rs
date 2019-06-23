use std::process;

const DRD: u8 = 0;

struct Memory {
    ram: [u8; 128],
    dreg: [u8; 64],
    areg: [u8; 64]
}

impl Default for Memory {
    fn default() -> Memory {
        return Memory {
            ram: [0; 128],
            dreg: [0; 64],
            areg: [0; 64]
        }
    }
}

// fn find_address_mode(code:u16, place:u8) -> u8 {

// }

fn get_source(mem:Memory, code:u16, eam:u8, place:u8) -> u32 {
    match eam {
        DRD => {
            let mut reg_num: u16 = code.clone();
            reg_num >>= place;
            reg_num &= 0b0000000000000111;
            return mem.dreg[reg_num as usize] as u32;
        },
        _ => {
            process::exit(1);
        }
    }
}

fn main(){
    // let timer = timer::Timer::new();
    // let (tx, rx) = channel();
    // let _guard = timer.schedule_with_delay(chrono::Duration::milliseconds(3), move || {
    //     // This closure is executed on the scheduler thread,
    //     // so we want to move it away asap.

    //     let _ignored = tx.send(()); // Avoid unwrapping here.
    // });

    // rx.recv().unwrap();
    // println!("This code has been executed after 3 seconds");

    let mut mem = Memory::default();
    mem.dreg[3] = 87;
    let code:u16 = 0b1101011100010001;
    // find_address_mode(code);
    // println!("{ }", 0b1101000100010001);
    println!("{ }", get_source(mem, code, DRD, 9));
}


