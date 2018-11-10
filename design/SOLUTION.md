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
Solution 01) For correctly parsing the subtitle file. We follows the order of the format of SRT file.
The goal is that we setup a method is it not only correctly read the normal SRT file, but also deal well with the corrupted file.
	
The general apporaching is, read the text file line by line. 
For each line, we indicate the Type of string of line.

We use an array, called marked array. Each array element contains two properties: marked_type and value.

We sequentially read the SRT file line by line. For each line, indicate the line's "MarkType". Then we look at the marked array, do these following steps: 
	- If marked array is empty, then current line's MarkType must equal to 1, if it is not, report that this SRT file is invalid - we break the readline procedure and quit algorithm.
	- If marked array is not empty, take the latest element of array, called L. If Next_cycle_3(L's marked_type) == MarkType, then we push the current line to the end of array. If it is not, then report that this SRT file is invalid - we break the readline procedure quit algorithm.

Comment: 
	- The obstacle of the algorithm for finding the answer is that: 	
		i) What happens if the subtitle is a string which is similar to index or subtitle time? It make us confuse.
	- The obstacle of the algorithm for finding 

	We define some basic concepts:
	Type(s), next_cycle_3(t).
	Type(s) = 1; if s is a number
	          2; if s is a subtitle time.
			  3; if s is a content.
			  4; if s is a blank/empty string.

Solution_02) 
The input for this problem is the marked_array, the output of solution_01.
We create an output array. Each element of output array is the a SubTitleLine.

	S1) Initialize the output array as an empty array.
	S2) Incrementally build the output array by looping through each element of marked_array.
		For each element E: We have two choice, append E to the output array, or concat E with the last element of output array. To determine which choice would be used, we check the value of E and use a half_flag. If half_flag = 0.5, it means that the last element of output array is building, and we should use the choice 2. If half_flag = 0, it means that the last element of output array has been completely constructed, and it is time to append new value to output array (choice 1).

		The initial value of half_flag is 0.
		For each element E of marked array - do do these checks:
			if half_flag = 0:
				Append E to output array.
				Update value of half_flag to 0.5, to indicate that the newly element is building.
			if half_flag = 0.5:
				If E.content.trim().endsWidth(".") or E is the last element of input, then we do:
					Concat E into the last element of output by:
							concat E.content to last element.content
							last_element.toTime = E.toTime
					Update half_flag = 0, to indicate that the last value of output array has been completely built.
				If !E.content.trim().endsWith(".") or E is not the last element, then we do:
					Concat E into the last element of output by:
							concat E.content to last element.content
							last_element.toTime = E.toTime
					
Solution_03) 
For effective grouping sentences by blocking time, firstly, we do the solution_02 to convert raw subtitle data into Subtitle data by sentences.

We call that is the input array. Then we do a procedure for grouping. Since we group by time, Let's choice time is the main criteria. Starts with range [0,BlockTime), merge every input elements E which sastifies the condition (E.fromTime >= 0 and E.toTime < BlockTime).

Let's build every element of output. 
The 1_st solution - Virtual ruler:
	User a "virtual" ruler. 
		- Arrange input elements to Time axis.
	Then repeatly use ruler to indicate what elements should be inserted into array.
	The ruler's length is equal BlockTime, initially, anchor point = the beginning time of first element of input(input[0]).
	Use a label to count how many input has been processed, we call it processed_label, inital value of processed_label is zero.

	We repeatly do these procedures until all many input element has been processed, or processed_label = length of input:
		Put the ruler start at anchor point. 
		Start scan each input elements, start from processed_label position, to find how many input elements overlap the ruler. We stop scanning once we have found an element which do not overlap the ruler, or we reach the end of input array.

![Use virtual ruler](https://github.com/spidervn/subtitle_manupilation/blob/master/design/virtual_ruler.jpeg)

		Since, the ruler length is greater than 0, and the anchor point is at the beginning of an unprocessed element, there are at least one element which overlap the ruler (*).

		Enumerate all overlapped elements in ascending order, concat every content into a concated string. We create a new element E, which E.content is equal concated_string, E.fromTime is equal to the fromTime of the 1st overlapped elements, and E.toTime is equal to the toTime of the last overlapped elements. 
		Append the new E to the output array.

		We mark every overlapped elements as processed by increasing process_label to the number of overlapped elements. 

		Move the anchor point to the start (fromTime) of the next un-processed input element. 

		Repeat this procedure until all input element has been processed.

	The output array is the result.
