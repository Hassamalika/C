# Implement a program that identifies a person based on their DNA.
from sys import argv, exit
import csv

def max_str(s, sub):
    #calculate the max amount of times a STR is repeated
    #linear algorithm: O(len(s)) time complexity 0(len(s)) space complexity 
    #s:   [ATATATTATAT]
    #ans: [30201002010] -  how many times does sub repeat in s
    #sub: AT
    
    ans = [0] * len(s)
    for i in range(len(s) - len(sub), -1, -1):
        if s[i: i + len(sub)] == sub:
            if i + len(sub) > len(s) - 1:
                ans[i] = 1
            else:
                ans[i] = 1 + ans[i + len(sub)]
    return max(ans)
        
def print_match(reader, actual):
    for line in reader:
        person = line[0]
        values = [int(val) for val in line[1:]]
        if values == actual:
            print(person)
            return
    print("No match")

def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
        
    csv_path = argv[1]
    with open(csv_path) as csv_file: #closes file after opened
        reader = csv.reader(csv_file)    
        #for row in reader:
            #print(row)
        all_seq = next(reader)[1:] #ignore 'name' string, and focus on values
            
        txt_path = argv[2]
        with open(txt_path) as txt_file:
            s = txt_file.read()
            actual = [max_str(s, seq) for seq in all_seq]
        
        print_match(reader, actual)


if __name__ == "__main__":
    main()
