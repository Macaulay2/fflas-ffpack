% ftrsm right - upper - size(A) == size(B) - alpha=1
function errCode = ftrsm_test_02(p)
  errCode = 0;
  try
    addpath(p);
    ff_rand_init();
    F = ff_init_Field();
    n = ff_init_Size();
    B = ff_init_Matrix(F,n,n);
    A = ff_init_Matrix(F,n,n);
    A = triu(A);
    ff_res = ftrsm(F, 'Right', 'Upper', 'NonUnit', 1, A, B);
    ref_res = modb( ff_res*A,F);

    eq = isequal(ref_res, B);
    if ~eq
      error('Computation error');
    end
  catch exception;
    disp(exception.message);
    errCode = 1;
  end
end