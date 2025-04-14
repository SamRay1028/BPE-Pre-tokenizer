# BPE-Pre-tokenizer
Pre-tokenizes data on white space

This program is a custom pre-tokenizer implementation for the purposes of pre-tokenizing text data on white space.
It is important to note that this code does not include an actual BPE algorithm. The code focuses on preparing the data
necessary to implement the BPE training process and begin creating a vocabulary. This includes, counting word and pair 
frequencies, establishing which pairs appear in which words, etc.

This program makes use of the Robin hood hash map for greate memory efficiency and speed. The file, "robin_hood.h" is not included in this repository but can be found at the following link: https://github.com/martinus/robin-hood-hashing/blob/master/src/include/robin_hood.h

Over 5.6 mb of data (specifically the the complete works of William Shakespeare) and using only one CPU core this pre-tokenizer is able to run in 2-4 seconds using approximately 12-18 mb of RAM.

