"""A* routing demonstration in Python, 3rd project of the Udacity Introduction to Self Driving Cars Nanodegree

   Copyright (c) 2017 by Michael Ikemann"""

import math

class AStarPathNode:
    """Defines a single node within a tree of visited nodes
    
    Properties:
    total_costs: The total (effective) costs from the start to this node
    assumed_costs_to_destination: The total costs + the heuristic to the final destination
    previous_node: Backlink the the previous node"""
    
    def __init__(self, initial_costs, assumed_costs_to_destination, previous_node):
        """Constructor
        
        initial_costs: The effective costs from the start to this node
        assumed_costs_to_destination: The effective costs to this node plus the heuristic distance to the destination
        previous_node: Index of the previous node"""
        self.total_costs = initial_costs
        self.assumed_costs_to_destination = assumed_costs_to_destination
        self.previous_node = previous_node

class AStarRouter:
    """Implementation of an A* router which finds the shortest path between two given node indices
    
    Properties:
    map_data: Holds the map data which contains a list of nodes (.intersections) and links between these
    intersections (.roads)
    tree: A dictionary and tree containing all visited nodes and theirs backtracable path
    goal: The index of the goal intersection
    frontier: The current frontier nodes set which define the still possible branches to the destination"""
    
    def __init__(self, map_data):        
        """Constructs the A* router
        
        map_data: A map network holding the properties intersections (.coordinates) and roads,
        a list of lists which define links from each intersection to other intersections"""

        self.map_data = map_data
        self.tree = {}
        self.goal = -1
        self.frontier = set()
        
    def beeline_dist(self,start,dest):
        """Returns the beeline distance between two given nodes
        
        start: Index of the start node
        dest: Index of the destination node
        return: The distance"""
        a = self.map_data.intersections[start]
        b = self.map_data.intersections[dest]
        x_diff = b[0]-a[0]
        y_diff = b[1]-a[1]
        return math.sqrt(x_diff**2 + y_diff**2)        
        
    def road_costs(self,start,dest):
        """Returns the (effective) costs for traveling along a given road.
        Because no road costs have been provided the beeline function will be used here as well.
        
        start: The start node
        dest: The destination node
        return: The distance"""
        return self.beeline_dist(start,dest)
        
    def expand_intersection(self,start,costs):
        """Expands an intersection which lets one tree leaf become a branch and creates new
        leafs at all potential, not yet visited destination nodes. If a destination node has
        been visited already it will be replaced if the costs to reach it from this node
        are lower than the costs from the previous node.
        If all potential target nodes are cheapter already or the networks ends here,
        this branch will effectively be abandoned because it removes itself from the frontier set
        in any case and is discontinued if it does not further expand itself"""
        # Remove from frontier, the new leafs will (if possible) become the new frontier
        # of this branch.
        self.frontier.remove(start)
        ### for all destinations
        for dest in self.map_data.roads[start]:
            # calculate total distances to new nodes and the heuristic to the goal node
            road_distance = costs+self.road_costs(start,dest)
            total_assumed_distance = road_distance + self.beeline_dist(dest,self.goal)
            
            # if the node has not been visited yet or is cheaper reachable from this new node set/replace it
            if not dest in self.tree or self.tree[dest].assumed_costs_to_destination>total_assumed_distance:
                self.tree[dest] = AStarPathNode(road_distance, total_assumed_distance, start) 
                self.frontier.add(dest)
                
    def cheapest_front_node(self):
        """Returns the currently cheapest frontier node with the highest potential to quickly reach the goal
        
        Result: The cheapest node. -1 if there are not frontier nodes anymore"""
        if len(self.frontier)==0: # Verify there still is a frontier
            return -1
        
        # use first node for defaults
        cheapest = next(iter(self.frontier))
        cheapest_costs = self.tree[cheapest].assumed_costs_to_destination
        # replace with node with lowest current_cost + heuristic to goal
        for front_node in self.frontier:
            node = self.tree[front_node]
            if node.assumed_costs_to_destination<cheapest_costs:
                cheapest_costs = node.assumed_costs_to_destination
                cheapest = front_node
                
        return cheapest
                
    def show_front_status(self, cheapest):
        """For logging purposes only. Shows the current frontier node set and it's distances
        
        cheapest: The current cheapest frontier node"""
        print("Current state:")
        for intersection in self.frontier:
            node = self.tree[intersection]
            print("{} {} {}".format(intersection, node.total_costs, node.assumed_costs_to_destination))
        print("New cheapest front node is {}".format(cheapest))
        
    def shortest_path(self, start, goal):
        """Finds the shortest path between given start node index and given goal node index
        
        start: The start node index
        goal: The goal node index
        Return: A list of note indices from start to goal containing the shortest possible way. 
        An empty array will be returned if no way could be found"""
        
        if start==goal: # if we started at the goal return the result directly
            return [goal]
        
        # clear the tree, set the goal
        self.tree = {}
        self.goal = goal

        # insert start node into the tree and set and expand it
        self.frontier = set([start])        
        self.tree[start] = AStarPathNode(0,self.beeline_dist(start,goal), -1)
        self.expand_intersection(start,0)
        
        target_reached = False
        
        cheapest_last = -1 # cheapest start node in previous turn
        
        while True:
            # Obtain the cheapest frontier node
            cheapest_next = self.cheapest_front_node()
            
            # self.show_front_status(cheapest_next)

            # If the goal is our newest, cheapest start node we have found the best solution
            if cheapest_next==goal:
                target_reached = True
                break
            
            # If we found a new valid frontier node expand it by all it's not yet entered destination nodes
            if cheapest_next!=-1:
                node = self.tree[cheapest_next]
                self.expand_intersection(cheapest_next,node.total_costs)
                                
            if cheapest_last==cheapest_next:
                # this happens only if start and goal are not connected and
                # we could not get any closer to the target / try another way
                return []
            
        # backtrace our tree to build the node's list
        result = []        
        if target_reached:
            cur_index = goal
            while cur_index!=-1:
                cur_node = self.tree[cur_index]
                result.append(cur_index)
                # print(cur_index)
                cur_index = cur_node.previous_node
                
            result.reverse()
                
        return result
            
def shortest_path(M,start,goal):
    """Finds the shortest path between given start node index and given goal node index
    
    M: Contains the map data, .intersections contains a list of node coordinates and .roads the destinations of each node
    start: The start node index
    goal: The goal node index
    Return: A list of note indices from start to goal containing the shortest possible way. 
    An empty array will be returned if no way could be found"""
    
    router = AStarRouter(M)
    result = router.shortest_path(start,goal)
    return result