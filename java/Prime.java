class prime {
  public static void main(String[] args) {
    int last = 1000000;
    int found = 4;
    System.out.println("Prime numbers to " + last);
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
        // System.out.print(", " + number);
      }
    }
    long end = System.nanoTime();
    System.out.print("\nI found " + found + " prime numbers.");
    System.out.print("This took me " + ((end - start) / 1000000000.0) + " seconds.");
  }
}
