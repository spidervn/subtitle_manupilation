# Input
Input_01. What is the format of subtilte input file?

The subtitle input file is a SRT extension file.
SRT is perhaps the most basic of all subtitle formats. It consists of four parts, all in text.
	1) A number indicating which subtitle it is in the sequence.
	2) The time that the subtitle should appear on the screen, and then disappear.
	3) The subtitle itself.
	4) A blank line indicating the start of a new subtitle.
Here is an example SRT file: 

	1
	00:02:17,440 --> 00:02:20,375
	Senator, we're making
	our final approach into Coruscant.

	2
	00:02:20,476 --> 00:02:22,501
	Very good, Lieutenant.

# Problems 
Problem 01. How do we parse the subtitle file?
Problem 02. How do we group subitles content by setences?
Problem 03. What is the the effective way to group sentences by blocking-time?

# Solutions
Solution 01. For correctly parsing the subtitle file. We follows the order of the format of SRT file.
The goal is that we setup a method is it not only correctly read the normal SRT file, but also deal well with the corrupted file.
	
The general apporaching is, read the text file line by line. 
For each line, we indicate the 

We define some basic concepts:
Type(s), next_cycle_3(t).
Type(s) = 1; if s is a number
          2; if s is a subtitle time.