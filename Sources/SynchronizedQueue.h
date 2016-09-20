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

template<typename T>
T SynchronizedQueue<T>::pop() {
	std::unique_lock<std::mutex> mlock(mutex_);
	while (queue_.empty()) {
		cond_.wait(mlock);
	}
	auto item = queue_.front();
	queue_.pop();
	return item;
}

template<typename T>
void SynchronizedQueue<T>::pop(T& item) {
	std::unique_lock<std::mutex> mlock(mutex_);
	while (queue_.empty()) {
		cond_.wait(mlock);
	}
	item = queue_.front();
	queue_.pop();
}

template<typename T>
void SynchronizedQueue<T>::push(const T& item) {
	std::unique_lock<std::mutex> mlock(mutex_);
	queue_.push(item);
	mlock.unlock();
	cond_.notify_one();
}

template<typename T>
void SynchronizedQueue<T>::push(T&& item) {
	std::unique_lock<std::mutex> mlock(mutex_);
	queue_.push(std::move(item));
	mlock.unlock();
	cond_.notify_one();
}


template<typename T>
size_t SynchronizedQueue<T>::size() {
	std::unique_lock<std::mutex> mlock(mutex_);
	size_t queue_size = queue_.size();
	return queue_size;
}