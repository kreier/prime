class Main {
  public static void main(String[] args) {
    int last = 100000;
    int found = 4;
    System.out.print("Prime numbers to ");
    System.out.println(last);
    System.out.print("2, 3, 5, 7, ");
    long start = System.nanoTime();
    for(int number = 11; number < last; number = number + 2) {
      boolean prime = true;
      for(int divider = 3; divider < (int) Math.sqrt(number) + 1; divider = divider + 2) {
        if(number % divider == 0) {
          prime = false;
          break;
        }
      }
      if(prime) {
        found++;
        // System.out.print(", ");
        // System.out.print(number);
      }
    }
    long end = System.nanoTime();
    System.out.print("\nI found ");
    System.out.print(found);
    System.out.println(" prime numbers.");
    System.out.print("This took me ");
    System.out.print((end - start) / 1000000000.0);
    System.out.println(" seconds.");
      
  // start = time.monotonic()
  // for number in range(11, last, 2):
  //     prime = True
  //     for divider in range(3, int(math.sqrt(number))+1, 2):
  //         if number % divider == 0:
  //             prime = False
  //             break
  //     if prime:
  //         found += 1
  //         if disp:
  //             print(number, sep=', ', end=' ')
  // end = time.monotonic()
  // print(f"\nThis took: {(end - start)} seconds.")
  // print(f"I found {found} prime numbers.")
    }
}
