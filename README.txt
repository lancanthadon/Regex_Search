Consider a folder structure that contains many files. Each folder can contain one or more sub-folders. Each file could be of any arbitrary size. Assume that the files are all in text format (letters, numbers, symbols and whitespaces). This code supports the following features:

1. Given a search word, display the number of times that word occurs per file.

2. Given a search word, display the lines on which that word occurs along with the    filename and line number.

3. Given a search phrase with a pattern, list the lines on which that pattern occurs    along with the filename and line number.
	a. A * indicates zero or more occurrences of any character. For example, the 	pattern “hello*world” (excluding quotes) would match the lines containing 	“helloworld”, “hello world” and “hello, world”.
	b. A ? indicates one or more occurrences of any character. For example, the 	pattern “hello?world” (excluding quotes) would match the lines containing 	“hello world” and “hello, world”, but not “helloworld”.
	c. The search patterns could be used in complex ways. E.g.: “I w?d rather 	have questions * can't be answered than answers that can't * questioned.”

4. Display a total frequency of all the words that occur across all the files.    Display them in descending order.

5. Check if all kinds of parenthesis are balanced. The files might contain (, {, [,   ), } and ]. If not balanced, show the lines along with the line number and    filenames where they are not balanced.

6. A search functionality that returns the file names that matches a search parameter by use the TF-IDF measure to identify files that closely match the search term.