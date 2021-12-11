#include "Chromosome.h"
#include "Population.h"
#include <iostream>
#include <time.h>
using namespace std;

int main()
{
    //srand((unsigned)time(NULL));
    Population maxone(10, 10, 0.7, 0.03);

    Chromosome bestChrom = maxone.getBestChromosome();
    int solution = bestChrom.getChromSize();
    int fittest = bestChrom.getFitness();

    // 진화과정
    int generation = 0;
    double crossRate = maxone.getCrossoverRate();

    Chromosome select1(solution);
    Chromosome select2(solution);
    while (true)
    {
        generation++;

        cout << "===============" << endl;
        cout << "Generation : " << generation << endl;

        maxone.draw();
        cout << "(Best) ";
        bestChrom.draw();

        if (fittest == solution || generation > 1000) break;

        //genetic operator
        int popsize = maxone.getPopSize();
        for (int i = 0; i < popsize; i += 2)
        {
            double rnd = rand() / (double)RAND_MAX; // crossover 수행 여부
            // selection
            select1 = maxone.selection();
            select2 = maxone.selection();
            if (rnd < crossRate) // crossover가 일어나지 않으면 mutation 또한 일어나지 않는다.
            {
                // crossover
                maxone.crossover(select1, select2);
                // mutation
                maxone.mutation(select1);
                maxone.mutation(select2);

                select1.calcFitness();
                select2.calcFitness();
            }
            maxone.pushChromToPop(i, select1);
            maxone.pushChromToPop(i + 1, select2);
        }

        maxone.evaluation();
        maxone.copyPopToOld();

        bestChrom = maxone.getBestChromosome();
        maxone.pushChromToPop(0, bestChrom);

        fittest = bestChrom.getFitness();
    }
    cout << "(Selected Best) ";
    bestChrom.draw();
}