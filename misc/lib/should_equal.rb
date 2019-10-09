require_relative 'colors.rb'

def should_equal(a, b, file)
	puts "a: "
	print a
	puts "b: "
	print b
	if a != b
		puts "Equality problem on #{file}".red
	else
		puts "#{file} passed with success !".green
	end
end

def should_equal_n(a, b, n, file)
	puts "a: "
	print a
	puts "b: "
	print b
	if a[0...n] != b[0...n]
		puts "Equality problem on #{file}".red
	else
		puts "#{file} passed with success !".green
	end
end

def should_not_equal(a, b, file)
	puts "a: "
	print a
	puts "b: "
	print b
	if a == b
		puts "Equality problem on #{file}".red
	else
		puts "#{file} passed with success !".green
	end
end