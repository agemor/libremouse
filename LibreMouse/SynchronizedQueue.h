#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class SynchronizedQueue {
public:
	T pop();
	void pop(T& item);
	void push(const T& item);
	void push(T&& item);
	size_t size();

private:
	std::queue<T> queue_;
	std::mutex mutex_;
	std::condition_variable cond_;
};