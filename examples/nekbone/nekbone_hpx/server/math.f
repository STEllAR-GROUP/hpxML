c-----------------------------------------------------------------------
      function mod1(i,n)
C
C     Yields MOD(I,N) with the exception that if I=K*N, result is N.
C
      MOD1=0
      IF (I.EQ.0) THEN
         return
      ENDIF
      IF (N.EQ.0) THEN
         WRITE(6,*) 
     $  'WARNING:  Attempt to take MOD(I,0) in function mod1.'
         return
      ENDIF
      II = I+N-1
      MOD1 = MOD(II,N)+1
      return
      END
