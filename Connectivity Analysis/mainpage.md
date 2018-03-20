CSC 315 - Project 4 - Mainpage {#mainpage}
==============================
Course Information
------------------
###Authors
- Manasi Paste
- Dakotah Rusley

###Date
Nov. 9, 2017

###Professor
Dr. Paul Hinker

##Program Description
This program performs connectivity analysis on a given image, in order to more accurately pick out
connected components. This is done by first reading in an image file, converting to grayscale, and then "thresholding" the pixels of the file such that anything over a certain threshold is marked. 
It then categorizes the different "groups" by treating the cells as a graph and traversing the graph, marking connected nodes. The program finishes by randomly assigning colors to these groups, making the 
different groups stand out from one another. 

To do connectivity analysis we do image segmentation, in which image pixels are partitioned into meaningful regions. Connectivity analysis performs this task by labeling the connected components in an image. Given  a  grayscale  image, binary  thresholding is  applied to  produce  a  binary  image.  All image  pixels  below  a threshold are set to 0 (black), and all pixels above a threshold are set to 1(white). The binary image consists of irregularly-shaped white regions (“blobs”) on a uniform black background. Each blob is a connected component of the image. Connectivity analysis assigns a unique label to each connected component in the binary image. Every pixel in a blob is assigned the same label, allowing blobs to be displayed in different colors.

Size Filtering is displaying only the blobs with number of pixels higher than a certain number. This is done by producing a pixel frequency distribution known as image histogram. If there are fewer than the specified number of pixels thery are set to zero.

##Compile Section

###Build

@verbatim
% conncomp image.PNG [binary_threshold (128) ] [size_threshold (32)]
@endverbatim

###Usage

##To Do, Bugs, and Modifications

###Bugs

###Revision History

https://gitlab.mcs.sdsmt.edu/7404855/csc315_fall2017_project4.git
