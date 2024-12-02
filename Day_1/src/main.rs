use std::fs;
use std::collections::HashMap;

fn puzzle1(vec1: &Vec<i32>, vec2: &Vec<i32>) {
    let mut vecMask1 : Vec<u32> = vec![0; vec1.len().try_into().unwrap()];
    let mut vecMask2 : Vec<u32> = vec![0; vec2.len().try_into().unwrap()];

    let mut index1 = 0;
    let mut index2 = 0;
    let mut curr1 = std::i32::MAX;
    let mut curr2 = std::i32::MAX;
    let mut totalDelta = 0;

    let mut outerIndex = 0;
    
    loop {
        let mut index = 0;
        while index < vec1.len() {
            let temp1 = vec1[index];
            let temp2 = vec2[index];

            if vecMask1[index] != 1 && temp1 < curr1 {
                curr1 = temp1;
                index1 = index;
            }
            if vecMask2[index] != 1 && temp2 < curr2 {
                curr2 = temp2;
                index2 = index;
            }
            index += 1;
        }
        totalDelta += (curr1 - curr2).abs();
        vecMask1[index1] = 1;
        vecMask2[index2] = 1;

        outerIndex += 1;
        if outerIndex >= vec1.len() {
            break;
        }

        curr1 = std::i32::MAX;
        curr2 = std::i32::MAX;
    }

    println!("totalDelta: {}", totalDelta.to_string())

}

fn puzzle2(vec1: &Vec<i32>, vec2: &Vec<i32>) {
    let mut accum = 0;
    let mut vecCount : Vec<i32> = vec![];
    let mut mapNumberToCountIndex : HashMap<i32, u32> = HashMap::new();

    for i in vec2 {
        if mapNumberToCountIndex.contains_key(i) {
            vecCount[*mapNumberToCountIndex.get(i).unwrap() as usize] += 1;
        } else {
            let index = vecCount.len();
            vecCount.push(1);
            mapNumberToCountIndex.insert(*i, index.try_into().unwrap());
        }
    }

    for j in vec1 {
        if mapNumberToCountIndex.contains_key(j) {
            accum += j * vecCount[*mapNumberToCountIndex.get(j).unwrap() as usize];
        }
    }
    println!("accumulation: {}", accum.to_string());
}

fn main() {
    let inputStr: String = fs::read_to_string("./input 1.txt").expect("Something went wrong.");
    let lineCount = inputStr.lines().count();
    let mut vec1 : Vec<i32> = Vec::with_capacity(lineCount);
    let mut vec2 : Vec<i32> = Vec::with_capacity(lineCount);

    for line in inputStr.lines() {
        let mut lineData : Vec<&str> = line.split(" ").collect();
        lineData.retain(|&val| !val.is_empty());


        vec1.push(lineData[0].parse::<i32>().unwrap());
        vec2.push(lineData[1].parse::<i32>().unwrap());
    }
    //puzzle1(&vec1, &vec2);
    puzzle2(&vec1, &vec2);
}