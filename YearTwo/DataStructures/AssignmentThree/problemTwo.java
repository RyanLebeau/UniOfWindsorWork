/**
 * Finished by: Ryan Lebeau - 104535367
 * 60-212
 * 2017/11/03
 * PrimeGenerator
 */

import java.util.Scanner;

public class problemTwo {
    public class PrimeGenerator
    {
        private int current;
        public PrimeGenerator()
        {
            current = 1;
        }
        /**
         Calculates the next prime number.
         @return the next prime number
         */
        public void nextPrime(int limit)
        {
            for(int i=2; i<=limit; i++){
                if(isPrime(i)){
                    System.out.println(i);
                }
            }

        }
        /**
         Check if n is a prime number.
         @param n to check whether it is prime or not
         @return true if n is prime
         */
        public  boolean isPrime(int n)
        {
            for(int i=2; i<n; i++){
                if(n%i==0)
                    return false;
            }
            current = n;
            return true;
        }
    }

    /**
     This class prints prime numbers.
     */
    public class PrimePrinter
    {
        public void main (String[] args)
        {
            Scanner in = new Scanner(System.in);
            System.out.print("Enter upper limit: ");
            int limit = in.nextInt();
            PrimeGenerator primes = new PrimeGenerator();
            primes.nextPrime(limit);

        }
    }

}
