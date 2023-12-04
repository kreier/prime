class prime {
  public static void main(String[] args) {
    int last = 100000;
    int found = 4;
    System.out.println("Prime numbers to " + last + " in Java v0.8.1989");
    long start = System.nanoTime();
    for(int number = 11; number < last; number = number + 1) {
      boolean prime = true;
      for(int divider = 2; divider < number + 1; divider = divider + 1) {
        if((float)number/divider == (int)number/divider) {
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
    System.out.print("I found " + found + " prime numbers. ");
    System.out.print("This took me " + ((end - start) / 1000000000.0) + " seconds.");
  }
}
