// RequestQueue.h
#pragma once
#include <queue>
#include <memory>
#include "RideRequest.h"

// Comparator — lower requestId = higher priority (FIFO within same type)
// You can change this logic later to factor in RequestType
struct RequestComparator {
    bool operator()(const std::shared_ptr<RideRequest>& a,
                    const std::shared_ptr<RideRequest>& b) const {
        return a->getRequestId() > b->getRequestId();  // min-heap by ID
    }
};

class RequestQueue {
private:
    std::priority_queue<
        std::shared_ptr<RideRequest>,
        std::vector<std::shared_ptr<RideRequest>>,
        RequestComparator
    > pq;

    int totalEnqueued;

public:
    RequestQueue();

    void enqueue(std::shared_ptr<RideRequest> request);
    std::shared_ptr<RideRequest> dequeue();
    std::shared_ptr<RideRequest> peek() const;

    bool isEmpty()          const;
    int  size()             const;
    int  getTotalEnqueued() const;
    void display()          const;
};