let temp_path = system('sed "s/\(hw_modules\).*/\1/" <<< $PWD')
let root_path = substitute(temp_path, '\n\+$', '', '')
let final_path = root_path . '/**'
exe 'set path+=' . final_path
