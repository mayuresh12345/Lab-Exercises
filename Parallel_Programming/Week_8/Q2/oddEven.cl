__kernel void oddEven(__global int*A){
	int n = get_global_size(0);
	int id=get_global_id(0);
	int temp;
	
	if(id%2==1 && id+1<n)
	  {
	  	if(A[id]>=A[id+1])
	  	 {
	  	 	temp=A[id];
	  	 	A[id]=A[id+1];
	  	 	A[id+1]=temp;
	  	 }
	  }
}

