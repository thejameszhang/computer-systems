/* 
* Name: James Zhang
* UID: 118843940
* Course: CMSC216 by Professor Yoon
* Section: 0301
*/

#include <stdio.h>
#include <math.h>
#define MAX_LENGTH 50

/*
Calculates the numeric score after removing the nd lowest values and
taking into account days late and the points penalty
Args:
   - 1 x na array of scores
   - 1 x na array of weights
   - 1 x na array of days_late
   - int length of the arrays
   - int nd
   - int points_penalty
Returns:
   - double numeric_score
*/
static double calculate_score(int scores[], int weights[], 
      int days_late[], int length, int nd, int points_penalty) {

   int i, j, temp;
   double numeric_score, min = 100.0, score, sum, total_weight, value;

   /* for nd iterations, find lowest value and remove weights and scores*/
   for (i = 0; i < nd; i++) {
      for (j = 0; j < length; j++) {
         value = scores[j] * weights[j] / 100.0;
         if (value < min && value != 0) {
            min = value;
            temp = j;
         }
      }

      /* reset certain values after each iteration */
      min = 100.0;
      scores[temp] = 0;
      weights[temp] = 0;
      temp = 0;
   }

   /* now calculate the numeric score */
   for (i = 0; i < length; i++) {

      /* take off points for lateness */
      score = scores[i] - (points_penalty * days_late[i]);
      total_weight += weights[i];
      if (score < 0) {
         score = 0;
      }

      /* multiply by the individual weight */
      score = score * (weights[i] / 100.0);
      sum += score;
   }
   numeric_score = (double) sum / (total_weight / 100.0);
   return numeric_score;
}

/*
Calculates the mean of the assignment scores
Args:
   - 1 x na array of scores
   - 1 x na array of days late
   - int length
   - int points penalty
Returns:
   - double mean
*/
static double calculate_mean(int scores[], int days_late[], int length, 
                     int points_penalty) {
   int i, sum;
   double mean; 

   /* add sums and take into account lateness*/
   for (i = 0; i < length; i++) {
      sum += scores[i] - (points_penalty * days_late[i]);
   }
   mean = (double) sum / length;
   return mean;
}

/*
Calculates the standard deviation given the mean
Args:
   - 1 x na array of scores
   - 1 x na array of days late
   - int points_penalty
   - int length
   - double mean
Returns: 
   - double std
*/
static double calculate_std(int scores[], int days_late[], 
                     int points_penalty, int length, double mean) {
   
   int i;
   double sum = 0.0;

   /* sum squares of the differences */
   for (i = 0; i < length; i++) {
      sum += pow(scores[i] - (points_penalty * days_late[i]) - mean, 2);
   }
   return sqrt(sum / length);
}

/*
Checks to see if the sum of the weights is 100
Args:
   - 1 x na array of weights
Returns:
   - int valid
*/
static int check_weights(int weights[], int length) {
   int j, sum = 0;
   for (j = 0; j < length; j++) {
      sum += weights[j];
   }
   return sum == 100;
}

/*

*/
int main() {

   /* general information */
   int points_penalty, nd, na, i;
   char stats;

   /* assignment information */
   int num, score, weight, days_late;
   int assignments[MAX_LENGTH] = {0};
   int scores[MAX_LENGTH] = {0};
   int weights[MAX_LENGTH] = {0};
   int days[MAX_LENGTH] = {0};

   /* final information */
   double numeric_score, mean, std;
   
   /* scanf for some user info*/
   scanf(" %d %d %c", &points_penalty, &nd, &stats);
   scanf(" %d", &na);

   /* populating arrays with data */
   for (i = 0; i < na; i++) {
      scanf(" %d, %d, %d, %d", &num, &score, &weight, &days_late);
      assignments[num-1] = num;
      scores[num-1] = score;
      weights[num-1] = weight;
      days[num-1] = days_late;
   }

   /* check that the weights sum to 100 */
   if (!check_weights(weights, na)) {
      printf("ERROR: Invalid values provided\n");
      return 1;
   }

   /* printing final information */
   numeric_score = calculate_score(scores, weights, 
                                 days, na, nd, points_penalty);
   printf("Numeric Score: %5.4f\n", numeric_score);
   printf("Points Penalty Per Day Late: %d\n", points_penalty);
   printf("Number of Assignments Dropped: %d\n", nd);
   printf("Values Provided: \n");
   printf("Assignment, Score, Weight, Days Late\n");
   
   /* print the values provided */
   for (i = 0; i < na; i++) {
      printf("%d, %d, %d, %d\n", assignments[i], 
      scores[i], weights[i], days[i]);
   }
   
   /* print stats if asked for it */
   if (stats == 'Y' || stats == 'y') {
      mean = calculate_mean(scores, days, na, points_penalty);
      std = calculate_std(scores, days, points_penalty, na, mean);
      printf("Mean: %5.4f, Standard Deviation: %5.4f\n", mean, std);
   }
   return 0;
}
