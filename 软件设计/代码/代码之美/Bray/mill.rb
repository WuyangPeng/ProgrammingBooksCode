

lines = 0
interval = ARGV[0].to_i || 1000
STDIN.each_line do |line|
  lines += 1
  puts line if (lines % interval) == 0
end
  
