#include "Population.h"

Population::Population(int popSize, int chromSize, double cRate, double mRate)
	: m_popSize(popSize), m_chromSize(chromSize), m_crossoverRate(cRate), m_mutationRate(mRate), m_totalFitness(0)
{
	m_population.resize(popSize);
	m_oldPop.resize(popSize);

	for (int i = 0; i < popSize; i++)
		m_population[i].resetChromosome(chromSize);

	evaluation();
	copyPopToOld();
}

Chromosome Population::selection()
{
	return Chromosome();
}

// ���� ������ ���������� ����� ���� �ε����� �������� ���ʿ��� gene1 �����ڰ�, �����ʿ��� gene2 �����ڰ� �����ȴ�.
void Population::crossover(Chromosome& gene1, Chromosome& gene2)
{
	int onePoint = m_chromSize * m_crossoverRate;
	for (size_t i = 0; i < m_population.size(); i++)
	{
		vector<int> temp;
		temp.resize(m_chromSize);

		for (int j = 0; j < onePoint; j++)
		{
			temp[j] = gene1.getChromosome[j];
		}
		for (int j = onePoint; j < m_chromSize; j++)
		{
			temp[j] = gene1.getChromosome[j];
		}

		m_population[i].setChromosome(temp);
	}
}

void Population::mutation(Chromosome& gene)
{
	// �������� �Ѱ��� �����ڰ� �������̵ȴ�.
	vector<int> mut = gene.getChromosome();
	int rnd = rand() / (double)RAND_MAX;
	int idx = m_chromSize * rnd;
	mut[idx] = rand() % 2;
	gene.setChromosome(mut);
}

void Population::evaluation()
{
}

void Population::copyPopToOld()
{
	for (int i = 0; i < m_popSize; i++)
		m_oldPop[i] = m_population[i];
}

void Population::draw()
{
	for (int i = 0; i < m_popSize; i++)
		m_population[i].draw();
}
