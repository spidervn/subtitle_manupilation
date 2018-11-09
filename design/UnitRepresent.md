# Heap

U1 = That's a good observation.

U2 = And this is true for any array. It doesn't matter what n is. 

U3 = Doesn't have the power of 2, or 2 minus 1, or anything like that.

U4 = They automatically satisfy the backseat property.

U5 = The reason this works, is because you're calling max-heapify multiple times. 

U6 = You satisfy the precondition.

U7 = Then you start with n/2.

U8 = You are going to see two leaves as your children.

U9 = But regardless of that, that's going to be a max-heap, because it's a leaf.

U10. And you need to put them together.

U11. That's a fairly straightforward process of attaching the leaves together.

U12. Then you do a bunch of other things that all work on leaves, because n/2-1 (n over 2 minus 1) is probably also going to have leaves as it's children, given the large value of n.

U13. There will be a bunch of things where you work on these level of nodes, if you will that all have leaves as children.

U14. That make sense?

U15. If you do a a straitforward analysis of this, what is the complexity of build-max-heap?

U16. In terms of analysis? 

U17. You have to sum up a bunch of arithmetic series, and so on. 

U18. A hand wavy argument is that you're doing basically, obviously no work for the leaves.

U19. For the next level, you may be doing two operations. 

U20. And so there is an increase in operations as you get higher and higher up.

U21. But there are fewer and fewer nodes as you at higher and higher up, right? 

U22. Because there's only one node that is the highest level node.

U23. That node has logarithmic number of operations, but it's only one node.

U24. The ones down on the bottom have a constant number of operations.

U25. I will put all of this down, and hopefully you'll be convinced by the time we've done some math here, or some arithmetic here.

U26. You can quantify what I just said fairly easily, as long as you're careful about the counting that we have to do.

U27. Analysis has a lot to do with counting. 

U28. We're just being more careful with the counting, as opposed to this straightforward argument that wasn't particularly careful with the counting. 

U29. So let's take a look at exactly this algorithm. 

U30. Where we say, max-heapify takes constant time for nodes that are one level above the leaves. 

U31. In general, O(l) time for nodes that are L levels above the leaves. 

U32. That's observation number one.

U33. Observation number two is that we have n/4 nodes with -- give or take one, depending on the value of n.

U34. I don't want to get hung up on floors and ceilings. 

U35. And in any case, we're eventually going to get an asymptotic result, so we don't have to worry about that. 

U36. We have n/4 nodes with level one, n/8 with level two, ..., and 1 node with log(n) level, which is the root.

U37. So this is decrease in terms of nodes as the work that you're doing increases.

U38. That's the careful accounting that we have to do.

U39. And so all I have to do now to prove to you that this is actually O(N)/(an order) and algorithm, is write a little summation that sums up all of the work across these different lavels.

U40. The total amount of work in the for-loop can be summed as n divided by 4, times 1, times c. 

U41. We don't need to argue about how much work is done at that one level, how many swaps, et cetera.

U42. I am going to set just to try and make this a little easier to look at, and easy to reason about-- I am going to set n/4 to 2 rasied to k, and I am going to simplify. 

U43. 

U44. 