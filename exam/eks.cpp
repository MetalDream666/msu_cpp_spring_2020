#include <iostream>
#include <fstream>
#include <thread>
#include <queue>
#include <string>
#include <condition_variable>

class FileSum
{
private:	
	void worker_function(int& this_sum)
	{
		bool already_finished(false);
		while(true)
		{
			if(!already_finished)
			{
				std::unique_lock<std::mutex> lock(num_mutex);
				while(!num_available)
				{
					num_cv.wait(lock);
				}
				if(stop)
					break;
				num_available = false;
			}

			bool isNum = false;
			int num;
			
			{
				std::lock_guard<std::mutex> guard(queueLock);
				if(!numQueue.empty())
				{
					num = numQueue.front();
					numQueue.pop();
					isNum = true;
				}
			}
			
			if (!isNum)
			{
				already_finished = false;
				continue;
			}
			else
			{
				this_sum += num;
				already_finished = true;
			}
		}
	}
		
public:
	
	FileSum()
	{
		stop = false;
		num_available = false;
	}
	
	int getSum(std::string filename)
	{
		int sum = 0;
		int num = 0;
		
		std::ifstream file(filename, std::ios_base::in);
		
		std::thread t1 = std::thread([=] { worker_function(sum1); });
		std::thread t2 = std::thread([=] { worker_function(sum2); });
				
		while(!file.eof())
		{
			file >> num;
			
			{
				std::lock_guard<std::mutex> guard(queueLock);
				numQueue.push(num);
			}
			
			num_available = true;
			num_cv.notify_one();
		}
		
		stop = true;
		num_cv.notify_all();
		t1.join();
		t2.join();
		
		sum = sum1 + sum2;
		
		file.close();	
		return sum;
	}

	std::queue<int> numQueue;
	std::mutex queueLock;
	std::mutex num_mutex;
	std::condition_variable num_cv;
	bool num_available;
	bool stop;
	
	int sum1 = 0, sum2 = 0;
};

int main(int argc, char** argv)
{
	std::string filename;
	
	if(argc < 2)
	{
		std::cout << "Please provide a filename" << std::endl;
		return 1;
	}
	else
	{
		filename = argv[1];
	}
	
	FileSum summer;
	int answer = summer.getSum(filename);
	
	std::cout << "The answer is: " << answer <<std::endl;
	
	return 0;
}
/*
Дан текстовый файл из строк (разделитель строк \n), в строке числа разделенные пробелами, пример:

1 45 6
31 5
6 8 9

Требуется написать программу считающую сумму всех чисел в файле, при этом должен быть поток который читает файл 
и должно быть 2 потока которые суммируют числа в строке. Числа целые, положительные, гарантированно помещаются в тип int. Результат тоже гарантированно помещается в тип int.

В конце работы в консоль выводится результат.

Подсчет должен идти одновременно с чтением файла.


Решения присылайте сюда:
m.trempoltsev@corp.mail.ru
Тема: Экзамен 
*/
