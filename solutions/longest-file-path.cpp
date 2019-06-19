/*
Daily Coding Problem #17: Longest File Path

This problem was asked by Google.

Suppose we represent our file system by a string in the following manner:

The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

dir
    subdir1
    subdir2
        file.ext

The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a
file file.ext.

The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
represents:

dir
    subdir1
        file1.ext
        subsubdir1
    subdir2
        subsubdir2
            file2.ext

The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file
file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level
sub-directory subsubdir2 containing a file file2.ext.

We are interested in finding the longest (number of characters) absolute path to a file within our
file system. For example, in the second example above, the longest absolute path is
"dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).

Given a string representing the file system in the above format, return the length of the longest
absolute path to a file in the abstracted file system. If there is no file in the system, return 0.

Note:

The name of a file contains at least a period and an extension.

The name of a directory or sub-directory will not contain a period.
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

/*
O(n) solution (single pass)

This solution parses the string, looking for '.' and '\'. A '.' indicates the substring is a file,
and a \' indicates the end of the substring. Then count the number of "\t"'s to find the depth of
the next item. From this we know whether to store the previous directory or whether to move back up
the filesystem and remove directories.

Directories are tracked with a stack
*/
int solution(string fs) {
    int depth = 0;
    int pathLength = 0;
    int maxLength = 0;
    bool isFile = false;
    stack<string> currentPath;
    for(int back = 0, front = 0; back < fs.length(); back++) {
        if(fs[back] == '.') {
            // found a '.' in the name, so this is a file
            isFile = true;
        }
        if(fs[back] == '\\' || back == fs.length() - 1) {
            // end of substring ("\n")
            string current = fs.substr(front, back - front);
            if(isFile) {
                // extra 1 for '/' after directory
                maxLength = max(maxLength, pathLength + (int)current.size() + 1);
                isFile = false;
            }
            // skip n
            back += 2;
            // count number of "\t"'s
            int i = back;
            while(fs[i] == '\\') {
                i += 2;
            }
            int numTs = (i - back) / 2;
            while(numTs < depth) {
                // end of directory, move back up
                depth--;
                // extra 1 for '/' after directory
                pathLength -= (currentPath.top().size() + 1);
                currentPath.pop();
            }
            if(numTs == depth + 1) {
                depth++;
                // extra 1 for '/' after directory
                pathLength += current.size() + 1;
                currentPath.push(current);
            }
            // back will be incremented by for loop, so subtract 1
            back = i - 1;
            front = i;
        }
    }
    return maxLength;
}

int main() {
    string in;
    cout << "Enter file system string:\n> ";
    cin >> in;
    cout << solution(in) << endl;
    return 0;
}