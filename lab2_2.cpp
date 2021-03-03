//Иванчук Евгения, 9894

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <semaphore.h>

using namespace std;

sem_t sem;
bool flag = true;

void* func1(void *arg)
{
	int *npt = (int*) arg;
	int n = *npt;
	while (flag == 1)
	{
		int rv = sem_trywait(&sem);
		if (rv != 0)
		{
			sleep(1);
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				if (flag != 1)
				break;
				cout << "1";
				cout.flush();
				sleep(1);
			}
			sem_post(&sem);
			sleep(1);
		}
	}
	return NULL;
}

void* func2(void *arg)
{
	int *npt = (int*) arg;
	int n = *npt;
	while (flag == 1)
	{
		int rv = sem_trywait(&sem);
		if (rv !=0)
		{
			sleep(1);
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				if (flag != 1)
				break;
				cout << "2";
				cout.flush();
				sleep(1);
			}
			sem_post(&sem);
			sleep(1);
		}
	}
	return NULL;
}

int main()
{
	sem_init(&sem, 0, 1);
	int arg;
	cout << "Введите число повторений:" << endl;
	cin >> arg;
	cin.clear();
	pthread_t th1, th2;
	pthread_create(&th1, NULL, func1, (void*) &arg);
	pthread_create(&th2, NULL, func2, (void*) &arg);
	cin.ignore();
	getchar();
	flag = false;
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	sem_destroy(&sem);
	return 0;
}
