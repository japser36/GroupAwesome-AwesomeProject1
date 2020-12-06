typedef struct {

} PageTable;

PageTable createPageTable(){

}

/**
 * handleAddress
 *
 * Extracts information from a virtual address and prints it out in the format expected by the assignment.
 * @param {int} n The n lowest significant bits that represent the offset
 * @param {int} m The next m bits that represent the page number; assume that n+m is always 16
 * @param {unsigned int} v The virtual address that needs to be mapped to a page number and offset
 */
int handleAddress(int n, int m, unsigned int v) {
  // Do n and m also have to be marked unsigned?
	int p = v >> n;
  int d = v & ~((~0) << n); // create a mask similar to: 00...00011111 with n 1's, then & v
  // could probably also use:
  // int d = (v << m) >> m;
  printf("virtual address %d is in page number %d and offset %d\n", v, p, d);
  return 0; // would return p and d in a struct here probably, but seems its not required for this project.
}
