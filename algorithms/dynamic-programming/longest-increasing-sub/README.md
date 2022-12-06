# Longest Increasing Subsequence (LIS)

## Problem

Given an array of integers, find the length of the longest monotonically increasing (i.e. strictly increasing) subsequence. A subsequence is a sequence that can be derived from the original array by deleting some or no elements without changing the order of the remaining elements.  
More formally, given an array $nums$ of length $n$, find the length of the LIS such that $nums[i] < nums[j]$, for all $i < j \leq n$. Note that we are looking for both the length and an actual subsequence, which is not necessarily unique.  
For example, given the array $nums = [12, 8, 1, 4, 2, 9, 10, 18, 15, 7, 20]$, the LIS is $[1, 2, 9, 10, 15, 20]$, which has length 6.

## Brute Force Solution

A brute force solution would be to generate all increasing subsequences of the array and then find the longest one. The time complexity of this solution is $O(2^n)$, where $n$ is the length of the array.

Implementation: [LIS - Brute Force]