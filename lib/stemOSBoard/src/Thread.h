/*
 * Task.h
 *
 *  Created on: Mar 4, 2017
 *      Author: kolban
 */

#ifndef Thread_h
#define Thread_h

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string>
/**
 * @brief Encapsulate a runnable task.
 *
 * This class is designed to be subclassed with the method:
 *
 * @code{.cpp}
 * void run(void *data) { ... }
 * @endcode
 *
 * For example:
 *
 * @code{.cpp}
 * class CurlTestTask : public Task {
 *    void run(void *data) {
 *       // Do something
 *    }
 * };
 * @endcode
 *
 * implemented.
 */
class Thread {
public:
	Thread(std::string taskName = "Task", uint16_t stackSize = 10000, uint8_t priority = 5);
	void setStackSize(uint16_t stackSize);
    void setFunc(void (f)());
	void setPriority(uint8_t priority);
	void setName(std::string name);
	void setCore(BaseType_t coreId);
	void start(void* taskData = nullptr);
	void stop();
	static void delay(int ms);

private:
	xTaskHandle m_handle;
    static void (f)();
	void*       m_taskData;
	static void runTask(void* data);
	std::string m_taskName;
	uint16_t    m_stackSize;
	uint8_t     m_priority;
	BaseType_t  m_coreId;

};

#endif /* COMPONENTS_CPP_UTILS_TASK_H_ */
