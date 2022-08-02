
def count_one stream, counts
  stream.each do |line|

    # for example: From: Tim Bray <Tim.Bray@Sun.COM>
    if line =~ /^From: .*<([^>]*)>\n$/
      who = $1
      if counts[who]
        counts[who] += 1
      else
        counts[who] = 1
      end
    end
  end
end

counts = {}
if ARGV.length == 0
  count_one STDIN, counts
else
  ARGV.each do |filename|
    File.open(filename) { |file| count_one(file, counts) }
  end
end

descending = counts.keys.sort { |a, b| counts[a] <=> counts[b] }
descending.reverse_each { |from| puts "From: #{from}: #{counts[from]}" }
