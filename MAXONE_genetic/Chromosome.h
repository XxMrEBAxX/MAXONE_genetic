#pragma once
#include <vector>
using namespace std;

class Chromosome
{
	vector<int> m_genes;	// 염색체 스트링
	int m_chromSize;
	int m_fitness;			// 적합도
	double m_fitnessRate;	// 0 ~ 1 사이의 값. 전체 population에서 적합도 비율 ==> population에서 설정
public:
	Chromosome(int size = 5) { resetChromosome(size); };
	~Chromosome() {}

	void resetChromosome(int size); // 변수 초기화에 사용
	void initChromosome();	// 염색체 초기화

	// getters
	int getChromSize() { return m_chromSize; }
	int getFitness() { return m_fitness; }
	double getFitnessRate() { return m_fitnessRate; }
	vector<int> getChromosome() { return m_genes; }

	// setters
	void setFitnessRate(double fr) { m_fitnessRate = fr; }
	void setChromosome(vector<int> genes) { m_genes = genes; }

	void calcFitness();
	void draw();
};

