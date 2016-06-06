% ftrmm right - upper - size(A) != size(B) B is not square matrix - alpha=1
function errCode = ftrmm_test_07(p)
  errCode = 0;
  try
    addpath(p);
    ff_rand_init();
    F = ff_init_Field();
    m = ff_init_Size();
    n = ff_init_Size();
    alpha = ff_init_Element(F);
    B = ff_init_Matrix(F,m,n);
    A = ff_init_Matrix(F,n,n);
    A = triu(A);
    ff_res = ftrmm(F, 'Right', 'Upper', 'NonUnit', alpha, A, B);
    ref_res = modb(alpha*modb(B*A,F),F);
    eq = isequal(ref_res, ff_res);
    if ~eq
      error('Computation error');
    end
  catch exception;
    disp(exception.message);
    errCode = 1;
  end
end