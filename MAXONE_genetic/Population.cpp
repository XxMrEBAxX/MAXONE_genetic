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
	int selectIndex = 0;
	double rnd = rand() / (double)RAND_MAX;
	double selRate = 0.0;
	for (int i = 0; i < m_popSize; i++)
	{
		selRate += m_oldPop[i].getFitnessRate();
		if (selRate >= rnd)
		{
			selectIndex = i;
			break;
		}
	}

	return m_oldPop[selectIndex];
}

// 원점 교차로 교차비율에 사이즈를 곱한 인덱스를 원점으로 왼쪽에는 gene1 유전자가, 오른쪽에는 gene2 유전자가 복제된다.
void Population::crossover(Chromosome& chrom1, Chromosome& chrom2)
{
	/* 뇌피셜로 작성한 것 (크로스오버 포인트가 항상 일정하게 작동하는 것이 문제, 스왑핑 하지 않고 그저 새로운 교배된 크로모좀을 생성함)
	int onePoint = m_chromSize * m_crossoverRate;
	for (size_t i = 0; i < m_population.size(); i++)
	{
		
		vector<int> temp;
		temp.resize(m_chromSize);

		for (int j = 0; j < onePoint; j++)
		{
			temp[j] = chrom1.getChromosome[j];
		}
		for (int j = onePoint; j < m_chromSize; j++)
		{
			temp[j] = chrom2.getChromosome[j];
		}

		m_population[i].setChromosome(temp);
	}
	*/
	int crossPoint = rand() % m_chromSize;
	vector<int> genes1 = chrom1.getChromosome();
	vector<int> genes2 = chrom2.getChromosome();
	
	for (int i = 0; i < crossPoint; i++)
	{
		swap(genes1[i], genes2[i]);
	}
	chrom1.setChromosome(genes1);
	chrom2.setChromosome(genes2);
}

void Population::mutation(Chromosome& chrom)
{
	double rnd = rand() / (double)RAND_MAX; // double : 0 ~ 1 값
	if (rnd > m_mutationRate)
		return;

	int mutatePoint = rand() % m_chromSize;
	vector<int> genes = chrom.getChromosome();
	genes[mutatePoint] = 1 - genes[mutatePoint];
	chrom.setChromosome(genes);
}

void Population::evaluation()
{
	m_totalFitness = 0;
	int bestChromIndex = 0;
	
	int bestFitness = 0;

	for (int i = 0; i < m_popSize; i++)
	{
		m_population[i].calcFitness();
		int curChromFit = m_population[i].getFitness(); // i번째 크로모좀의 적합도
		if (curChromFit > bestFitness)
		{
			bestChromIndex = i;
			bestFitness = curChromFit;
		}
		m_totalFitness += curChromFit;
	}
	// 각 Chromosome의 FitnessRate 계산
	for (int i = 0; i < m_popSize; i++)
	{
		double curFitRate = m_population[i].getFitness() / (double)m_totalFitness;
		m_population[i].setFitnessRate(curFitRate);
	}
	m_bestChromosome = m_population[bestChromIndex];
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
