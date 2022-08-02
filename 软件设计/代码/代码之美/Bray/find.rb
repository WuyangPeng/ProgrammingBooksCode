require 'big-hash'
require 'binary-search'

# args are data file, test queries, and class-name to use 

data_file = ARGV[0]
query_file = ARGV[1]
class_name = ARGV[2]
array_size = ARGV[3].to_i

t0 = Process::times
puts "#{t0.inspect}"

if class_name == 'Hash'
  worker = BigHash.new(data_file)
elsif class_name == 'Binary'
  worker = BinarySearch.new(data_file, array_size)
end

queries = 0
t1 = Process::times
puts "#{t1.inspect}"
File.open(query_file).each_line do |line|
  line.chomp!
  y = worker.find(line)
  puts "ERROR, #{line} not found" unless y
  n = worker.find(line.reverse)
  puts "Oddly, #{line.reverse} was found" if n
  queries += 1
end
t2 = Process::times
puts "#{t2.inspect}"

puts "Queries #{queries}, load time #{t1.utime - t0.utime}, " +
  "run time #{t2.utime - t1.utime}"
