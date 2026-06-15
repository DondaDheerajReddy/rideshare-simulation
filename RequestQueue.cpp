// RequestQueue.cpp
#include "RequestQueue.h"
#include "RideshareExceptions.h" 
#include <iostream>
#include <stdexcept>

RequestQueue::RequestQueue() : totalEnqueued(0) {}

void RequestQueue::enqueue(std::shared_ptr<RideRequest> request) {
    pq.push(request);
    totalEnqueued++;
    std::cout << "Enqueued: " << request->getTypeString()
              << " Request #" << request->getRequestId() << "\n";
}

std::shared_ptr<RideRequest> RequestQueue::dequeue() {
    if (pq.empty())
        throw QueueEmptyException();
    auto top = pq.top();
    pq.pop();
    return top;
}

std::shared_ptr<RideRequest> RequestQueue::peek() const {
    if (pq.empty())
        throw QueueEmptyException();
    return pq.top();
}

bool RequestQueue::isEmpty()          const { return pq.empty(); }
int  RequestQueue::size()             const { return pq.size(); }
int  RequestQueue::getTotalEnqueued() const { return totalEnqueued; }

void RequestQueue::display() const {
    std::cout << "=== Request Queue (" << pq.size() << " pending) ===\n";
    // priority_queue doesn't support iteration, so just show the top
    if (!pq.empty())
        std::cout << "Next up: " << pq.top()->getTypeString()
                  << " #" << pq.top()->getRequestId() << "\n";
}