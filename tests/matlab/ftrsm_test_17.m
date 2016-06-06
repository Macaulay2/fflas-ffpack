% ftrsm left - upper - size(A) != size(B) B is not square matrix - alpha=1
function errCode = ftrsm_test_17(p)
  errCode = 0;
  try
    addpath(p);
    ff_rand_init();
    F = ff_init_Field();
    m = ff_init_Size();
    n = ff_init_Size();
    B = ff_init_Matrix(F,m,n);
    A = ff_init_Matrix(F,m,m);
    A = triu(A);
    A(1:m+1:m*m) = 1;
    ff_res = ftrsm(F, 'Left', 'Upper', 'Unit', 1, A, B);
    ref_res = modb( A*ff_res,F);

    eq = isequal(ref_res, B);
    if ~eq
      error('Computation error');
    end
  catch exception;
    disp(exception.message);
    errCode = 1;
  end
end