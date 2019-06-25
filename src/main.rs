use std::process;

const BYTE: u8 = 1;
const WORD: u8 = 2;
const LONG: u8 = 4;

const DRD: u8 = 0;
const ARD: u8 = 1;
const RI: u8 = 3;
const PIRI: u8 = 4;
const PDRI: u8 = 5;

struct Memory {
    ram: [u8; 128],
    dreg: [u8; 64],
    areg: [u8; 64],
    ssp: u32,
    usp: u32,
    pc: u32,
    sr: u16
}

impl Default for Memory {
    fn default() -> Memory {
        return Memory {
            ram: [0; 128],
            dreg: [0; 64],
            areg: [0; 64],
            ssp: 0,
            usp: 0,
            pc: 0,
            sr: 0
        }
    }
}

// fn find_address_mode(code:u16, place:u8) -> u8 {

// }

fn get_source(mem:Memory, code:u16, eam:u8, place:u8, size:u8) -> u32 {
    match eam {
        DRD => {
            let mut reg_num: u16 = code.clone();
            reg_num >>= place;
            reg_num &= 0b0000000000000111;
            reg_num *= 4;
            return get_long(&mem.dreg, reg_num as usize)
            // return mem.dreg[reg_num as usize] as u32;
        },
        ARD => {
            let mut reg_num: u16 = code.clone();
            reg_num >>= place;
            reg_num &= 0b0000000000000111;
            reg_num *= 4;
            return get_long(&mem.areg, reg_num as usize)
        },
        RI => {
            let mut reg_num: u16 = code.clone();
            reg_num >>= place;
            reg_num &= 0b0000000000000111;
            reg_num *= 4;
            let mut address = get_long(&mem.areg, reg_num as usize);
            return get_long(&mem.ram, address as usize);
        },
        _ => {
            process::exit(1);
        }
    }
}

fn set_dest(mem: &mut Memory, code:u16, eam:u8, place:u8, size: usize, value:u32) {
    let byte_values = split_bytes(value, size);

    for i in 0..size {
        println!("{ }", byte_values[i]);
    }
    
    match eam {
        DRD => {
            let mut reg_num: u16 = code.clone();
            reg_num >>= place;
            reg_num &= 0b0000000000000111;
            reg_num *= 4;
            
            for i in 0..size {
                mem.dreg[reg_num as usize + i] = byte_values[i];
            }
        },
        _ => {
            process::exit(1);
        }
    }
}

fn split_bytes(value: u32, size: usize) -> Vec<u8> {
    let mut bytes: Vec<u8> = vec![];
    let mut current = value.clone();
    for _ in 0..size {
        println!{"test"};
        bytes.push(current as u8);
        current >>= 8;
    }
    return bytes;
}

fn get_word(mem:&[u8], start:usize) -> u32 {
    if(start % 2 == 1) {panic!("Trying to address on an odd address")}
    return (mem[start + 1] as u32 *256) + mem[start] as u32;
}

fn get_long(mem:&[u8], start:usize) -> u32 {
    if(start % 2 == 1) {panic!("Trying to address on an odd address")}
    return (mem[start + 3] as u32 *16777216)
        + (mem[start + 2] as u32 *65536)
        + (mem[start + 1] as u32 *256) 
        + mem[start] as u32;
}

fn main() {
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
    // mem.dreg[4] = 255;
    // mem.dreg[5] = 87;
    let code:u16 = 0b1101001100010001;
    // find_address_mode(code);
    // println!("{ }", 0b1101000100010001);
    set_dest(&mut mem, code, DRD, 0, WORD as usize, 0xFA73);
    for i in 4..6 {
        println!("{ }", mem.dreg[i]);
    }
    // println!("{ }", get_source(mem, code, DRD, 9, LONG));
}
