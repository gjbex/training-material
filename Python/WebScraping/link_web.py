#!/usr/bin/env python

from argparse import ArgumentParser
from bs4 import BeautifulSoup
from collections import deque
import matplotlib.pyplot as plt
import networkx as nx
import sys
import urllib

def show_links(soup, out=sys.stderr):
    print("Opened start page '{0}'".format(soup.title.string), file=out)
    links = soup.find_all("a")
    for link in links:
        href = link.get('href')
        if href:
            print('\t{0}'.format(href), file=out)

def process_page(pages_to_do, pages_done, max_level, graph, verbose=False):
    if pages_to_do:
        page_url, level = pages_to_do.popleft()
        if level <= max_level:
            if verbose:
                print('{0}: {1}'.format(page_url, level))
            pages_done.add(page_url)
            try:
                page = urllib.request.urlopen(page_url)
                soup = BeautifulSoup(page, 'html5lib')
                links = soup.find_all("a")
                for link in links:
                    href = link.get('href')
                    if href and href.startswith('http'):
                        if href not in pages_done:
                            pages_to_do.append((href, level + 1))
                        graph.add_edge(page_url, href)
            except urllib.error.HTTPError:
                print('# warning: can not handle {0}'.format(page_url),
                      file=sys.stderr)
            except urllib.error.URLError:
                print('# warning: can not handle {0}'.format(page_url),
                      file=sys.stderr)

if __name__ == '__main__':
    arg_parser = ArgumentParser(description='create graph of hyperlinks')
    arg_parser.add_argument('url', help='URL to start link analysis at')
    arg_parser.add_argument('--max-level', type=int, default=3,
                            help='maximum link depth')
    arg_parser.add_argument('--out', help='file name for GraphML output')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='give verbose output')
    options = arg_parser.parse_args()
    pages_done = set()
    pages_to_do = deque()
    pages_to_do.append((options.url, 0))
    graph = nx.Graph()
    graph.add_node(options.url)
    while pages_to_do:
        process_page(pages_to_do, pages_done, options.max_level,
                     graph, options.verbose)
    print('total pages scraped: {0}'.format(len(pages_done)))
    if options.out:
        nx.write_graphml(graph, options.out)
    else:
        nx.draw(graph)
        plt.show()
