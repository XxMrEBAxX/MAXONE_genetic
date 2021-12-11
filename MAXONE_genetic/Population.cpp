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

// 원점 교차로 교차비율에 사이즈를 곱한 인덱스를 원점으로 왼쪽에는 gene1 유전자가, 오른쪽에는 gene2 유전자가 복제된다.
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
	// 무작위로 한개의 유전자가 돌연변이된다.
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
