class prime {
  public static int is_prime(int number){
    int flag_prime = 1;
    for(int divider = 3; divider < (int) Math.sqrt(number) + 1; divider = divider + 2) {
      if(number % divider == 0) {
        flag_prime = 0;
        break;
      }
    }
    return flag_prime;
  }

  public static void main(String[] args) {
    int last = 10000000;
    int found = 4;
    System.out.println("Calculation prime numbers to " + last + " in Java v3.0.2023.");
    long start = System.nanoTime();
    for(int number = 11; number < last; number = number + 2) {
      found += is_prime(number);
    }
    long end = System.nanoTime();
    System.out.print("I found " + found + " prime numbers. ");
    System.out.print("This took me " + ((end - start) / 1000000000.0) + " seconds.");
  }
}
