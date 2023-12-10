// Prime v5.0.2023 2023/12/10
// cycles through limits and writes to the filesystem

import java.lang.*;
import java.util.*;
import java.io.FileWriter;  // Import the File class
import java.io.IOException;  // Import the IOException class to handle errors

class divisor {
  public static int[] primes = new int[10000];
  public static int found = 4;
  public static int divisors;
}

class prime_logging {
  public static int is_prime(int number) {
    int flag_prime = 1;
    for(int divider = 3; divider < (int) Math.sqrt(number) + 1; divider = divider + 2) {
      if(number % divider == 0) {
        flag_prime = 0;
        break;
      }
    }
    return flag_prime;
  }

  public static void find_primes(int limit) {
    divisor.primes[0] = 3;
    divisor.primes[1] = 5;
    divisor.primes[2] = 7; 
    divisor.divisors = 3;
    for(int number = 11; number <= limit; number = number + 2) {
      if(is_prime(number) > 0) {
        divisor.found++;
        divisor.primes[divisor.found - 2] =  number;
      }
    }
    divisor.divisors = divisor.found - 1;
  }

  public static int is_prime_fast(int number) {
    int largest_divider = (int)Math.sqrt(number);
    int flag_prime = 1;
    for(int i = 0; i < divisor.divisors; i++) {
      if(number % divisor.primes[i] == 0) {
        flag_prime = 0;
        break;
      }
      if(divisor.primes[i] > largest_divider)
      {
          break;
      }
    }
    return flag_prime;
  }

  public static String elapsed_time(int seconds) {
    int hours = (int)(seconds / 3600);
    int minutes = (int)(seconds/60 - hours*60);
    int sec = (int)(seconds - minutes*60 - hours*3600);
    return String.format("%dh %dmin %ds", hours, minutes, sec);
  }

  public static void main(String[] args) {
    int scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000};
    int reference[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534};
    float time_calc[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i=0; i < scope.length; i++) {
      int last = scope[i];
      divisor.found = 4;
      System.out.println("Calculation prime numbers v5.0.2023 in Java to " + last + ".");
      long start = System.nanoTime();
      // start of code
      int limit = (int)Math.sqrt(last);
      if(limit % 2 == 0) {
        limit++;
      }
      System.out.print("Find primes numbers to " + limit + ". ");
      find_primes(limit);
      System.out.println("Found " + divisor.found + " primes. Now using them as divisors.");
      for(int number = limit + 2; number < last; number = number + 2) {
        divisor.found += is_prime_fast(number);
      }
      // end of code
      long duration = System.nanoTime() - start;
      System.out.println("I found " + divisor.found + " prime numbers. There are actually " + reference[i] + ".");
      System.out.print(String.format(Locale.getDefault(), "This took me %.6f seconds. ",  (duration / 1000000000.0)));
      System.out.println(elapsed_time((int)(duration/1000000000)) + "\n");
      time_calc[i] = (float)(duration / 1000000000.0);
      // save as a file
      String filename = String.format("%d.txt", scope[i]);
      try {
        FileWriter myWriter = new FileWriter(filename);
        myWriter.write("Calculation prime numbers v5.0.2023 in Java to " + last + ".\n");
        myWriter.write(String.format(Locale.getDefault(), "This took me %.6f seconds. \n",  (duration / 1000000000.0)));
        myWriter.close();
        System.out.println("Successfully wrote to the file.");
      } catch (IOException e) {
        System.out.println("An error occurred.");
        e.printStackTrace();
      }
    }
    // print summary
    System.out.println("\nCalculation prime numbers v5.0.2023 in Java");
    System.out.println("     last      time in seconds");
    for(int i=0; i < scope.length; i++) {
      System.out.print(String.format(" ".repeat(8-(int)(i*0.9+0.5))));
      System.out.print(String.format(" %d ", scope[i]));
      System.out.print(String.format(" ".repeat(6 - (int)Math.log10((int)(1 + time_calc[i])))));
      System.out.println(String.format(Locale.getDefault(),"%.6f ", time_calc[i]));
    }
    // create summary.txt
    try {
      FileWriter myWriter = new FileWriter("summary.txt");
      myWriter.write("Calculation prime numbers v5.0.2023 in Java\n");
      myWriter.write("     last      time in seconds\n");
      for(int i=0; i < scope.length; i++) {
        myWriter.write(String.format(" ".repeat(8-(int)(i*0.9+0.5))));
        myWriter.write(String.format(" %d ", scope[i]));
        myWriter.write(String.format(" ".repeat(6 - (int)Math.log10((int)(1 + time_calc[i])))));
        myWriter.write(String.format(Locale.getDefault(),"%.6f \n", time_calc[i]));
      }
      myWriter.close();
      System.out.println("Successfully wrote to the file.");
    } catch (IOException e) {
      System.out.println("An error occurred.");
      e.printStackTrace();
    }    
  }
}
