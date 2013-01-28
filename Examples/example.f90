!字典序，已知序列的全排序

program main
  integer::i,j,k,temp
  integer,parameter::n=5
  integer::a(n),b(n),c(n),d(n),e(n),p(n)
  logical::ma,mb,mc,md,me
  real::t1,t2

  call cpu_time(t1)
  k=1
  p = (/(i,i=1,n)/)
  a = p
  ma=.true.
  do while(ma)
     write(*,*) a
     ma = .false.
     call next(n,a,ma)
  enddo
  call cpu_time(t2)
  write(*,*) t2-t1,k
end program main

subroutine next(n,a,m)
  integer::i,j,k,n
  integer::a(n),b(n)
  logical::m

  do i = n-1,1,-1
     if (a(i) < a(i+1)) then !从右向左查找第一个左边比右边大的数
        m = .true. !如果不存在这样的i，m保持为F,排序结束
        exit
     endif
  enddo

  do j = n,i+1,-1
     if (a(i) <= a(j)) exit !从右向左查找比找到的a(i)大的数
  enddo
  temp = a(i)
  a(i) = a(j)
  a(j) = temp !调换a(i),a(j)

  b=a
  do k = i+1,n
     a(k) = b(n+i+1-k) !将a(i+1:n)反转
  enddo
end subroutine next