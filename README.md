# Motivation
It is often the case in many apps that the client's window/viewer dimensions (and hence width) is known. This algorithm uses this fact to layout images in rows and columns in an aesthetically pleasing way to given arbitrary widths. 

The results of this algorithm include: 
- Formats images to any given arbitrary width
- Original order of images is maintained
- All images within a row have the same height despite originals having different aspect ratios and heights

More specific details: 
- Trailing images get formatted at full width
- Uses greedy constraint, meaning you must supply a MAX_HEIGHT constraint. 

# Basic usage 
(TODO)

# Implementation details
You do not need to read this section in order to simply use the algorithm and call the function. This section goes into the implementation details of how the algorithm works in case you would like to write it yourself, or just are curious and would like to have a better understanding. Here the pseudocode/mathematical notions will be covered. For a coded version, simply read the source code.

For simplicity purposes, let's take an example. Suppose that we have a collection (array, list, etc.) of three photos which we would like to format within a view of width `W`, all of different aspect ratios and heights, like the following: 

![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/1.jpg?raw=true "three images") 

Simply all that we would like to do is figure out new dimensions for these photos so that they are laid out inline with eachother in a way that **all images within a given row are of equal height *and* maintain their respective aspect ratios.** Let's first consider their aspect ratios. We know the ratios of the following images (which we plan to maintain) are the following: 

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/2.gif?raw=true) 　　　![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/3.gif?raw=true) 　　　![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/4.gif?raw=true)

and we also know that would like to transform this collection into

![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/5.jpg?raw=true "formatted images")

where the height is the same for all images, as we can see from the diagram. Note that W within our coded function is the fixed width of our view, passed as a parameter. In other words, W is a **known variable** and so are w<sub>1</sub>, h<sub>1</sub>, w<sub>2</sub>, h<sub>2</sub>, w<sub>3</sub>, h<sub>3</sub>. We can use these known variables in order to solve for w<sub>1</sub>', w<sub>2</sub>', w<sub>3</sub>'. We also desire to figure out what H is, and this is the most complicated step of the problem. We shall address that last. Let's first consider how to find the new widths for our layout. 

To solve for w<sub>1</sub>', w<sub>2</sub>', w<sub>3</sub>', consider the aspect ratios once again. It is a prerequisite of the problem that the aspect ratios must stay the same between the new and old image sizes (in other words, they are equal). Therefore, we can write:

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/6.gif?raw=true) 　　　![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/7.gif?raw=true) 　　　![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/8.gif?raw=true)

and hence

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/9-1.gif?raw=true) 　　　![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/10.gif?raw=true) 　　　![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/11.gif?raw=true)

Solving for the primes, we see that

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/12.gif?raw=true) 　　　![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/13.gif?raw=true) 　　　![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/14.gif?raw=true) 　　　 　　　 　<sup>(1)</sup>

So we know that if we have H, we can find the new widths. Simple, isn't it?

We must know the value of H however to solve these equations. How do we determine H? The answer is that there are multiple ways that you can define what H is, but we must supply parameters in any case. One of the simplest and fastest (in time complexity) ways is to use **greedy** logic. Essentially, we will provide a parameter MAX_HEIGHT and add images until the row height is below this maximum. But how does this help us determine what our true height will be? Consider the following. 

By inspection of our most recent diagram, we know that

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/15.gif?raw=true)

Now we do something really cool. Notice by (1) we can substitute our values for w<sub>1</sub>', w<sub>2</sub>', w<sub>3</sub>' in the above equation so that

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/16.gif?raw=true)

Factoring out H from the left side yields

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/17.gif?raw=true)

Then, divide the width primes from either side of the equation to isolate H so that

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/18.gif?raw=true)

So that we have a value of H! Notice that all of the variables on the right side of the equation are known parameters. So where does the greedy part come in? We could have had one, two, three, or arbitrarily more images determining the H, not necessarily three as we showed. The height is a *larger number the less image dimensions* there are on the right side of the equation. Initially we first try adding one image, so that

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/20.gif?raw=true)

Suppose that this resulted in a really tall undesirable image since it spans the full width. Then we try to add another so that 

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/19.gif?raw=true)

Again, say the combined images still are too tall as their widths are too large. Their widths decrease as we add images. Then when we get to 

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/18.gif?raw=true)

which may be below the MAX_HEIGHT constraint. Essentially, to determine the correct H, we compute the height of a row of images and compare it to MAX_HEIGHT each iteration, and finally when the height of the test row is below MAX_HEIGHT, we return the row which will magically be nicely formatted from this logic. After we have this H, we finish the work and determine the widths for each image in the row, by our equation (1) that utilizes the H we just found. 

Doing this for every image will give potentially multiple rows.

#### Generalization
--- 

In the above example, we only showed that we can do this for less than three images. It can be shown by mathematical induction that we apply this to an arbitrarily sized collection of images so that multiple rows with image dimensions as columns are returned. Formally, 

Let H be a real number. Suppose that H is the maximum number such that H <= MAX_HEIGHT determined by 

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/21.gif?raw=true)

such that
&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/22.gif?raw=true)
. Then for each 1, 2, ..., n, 

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/23.gif?raw=true)

Message or talk to me if you wish to see the full formalized reasoning behind this inductive rule. 

#### Adding Gaps 
If you wish to have gaps between images, then their widths must be adjusted accordingly. Then, the height above is determined instead by 

&nbsp;&nbsp;&nbsp;&nbsp;![alt text](https://github.com/goggalore/dynamic-images/blob/master/docs/imgs/24.gif?raw=true)

where g is the gap length.
