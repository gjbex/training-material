#!/usr/bin/env python

import heapq
from queue import PriorityQueue
import random


def create_jobs():
    names = ['beast', 'fluent', 'beast', 'gromacs', 'amrvac']
    jobs = []
    for name in names:
        jobs.append((random.random(), name))
    return jobs

if __name__ == '__main__':
    random.seed(143545)
    jobs = create_jobs()
    job_queue = PriorityQueue()
    print('inserting into PriorityQueue')
    for job in jobs:
        print('{0}: {1:.4f}'.format(job[1], job[0]))
        job_queue.put(job)
    print('removing from PriorityQueue')
    while not job_queue.empty():
        job = job_queue.get()
        print('{0}: {1:.4f}'.format(job[1], job[0]))
    heap_list = []
    print('inserting into heapq')
    for job in jobs:
        print('{0}: {1:.4f}'.format(job[1], job[0]))
        heapq.heappush(heap_list, job)
    print('removing from heapq')
    while heap_list:
        job = heapq.heappop(heap_list)
        print('{0}: {1:.4f}'.format(job[1], job[0]))

