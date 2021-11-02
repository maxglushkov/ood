#include <climits>
#include <functional>
#include <iostream>
#include <optional>
#include <queue>
#include <stack>
#include "compress-decorator.hpp"
#include "crypt-decorator.hpp"
#include "file-stream.hpp"

template<typename Decorated, typename Decorator, typename ...Args>
auto GenerateDecorator(Args... args)
{
	return [=](std::unique_ptr<Decorated> && decorated)
	{
		return std::make_unique<Decorator>(std::move(decorated), args...);
	};
}

void PrintUsage(char const* programName)
{
	if (!programName)
	{
		programName = "streams";
	}
	std::cerr << "Usage: " << programName << " [--encrypt <key>|--decrypt <key>|--compress|--decompress]… <input-file> <output-file>\n";
}

std::optional<CCrypt::KeyType> ParseKey(std::string const& str)
{
	if (std::all_of(str.begin(), str.end(), isdigit))
	{
		try
		{
			return std::stoull(str);
		}
		catch (...)
		{}
	}
	std::cerr << "Encryption keys are non-negative integers not greater then " << ULONG_LONG_MAX << '\n';
	return std::nullopt;
}

int main(int argc, char const* argv[])
{
	if (argc < 3)
	{
		PrintUsage(*argv);
		return 1;
	}

	std::queue<std::function<IInputStreamPtr(IInputStreamPtr &&)>> inputWrappers;
	std::stack<std::function<IOutputStreamPtr(IOutputStreamPtr &&)>> outputWrappers;

	char const** arg = argv;
	while (++arg, --argc > 2)
	{
		using namespace std::literals;
		if (*arg == "--encrypt"s)
		{
			if (++arg, --argc > 2)
			{
				if (auto key = ParseKey(*arg))
				{
					outputWrappers.push(GenerateDecorator<IOutputDataStream, CEncryptOutputStream>(*key));
					continue;
				}
			}
		}
		else if (*arg == "--decrypt"s)
		{
			if (++arg, --argc > 2)
			{
				if (auto key = ParseKey(*arg))
				{
					inputWrappers.push(GenerateDecorator<IInputDataStream, CDecryptInputStream>(*key));
					continue;
				}
			}
		}
		else if (*arg == "--compress"s)
		{
			outputWrappers.push(GenerateDecorator<IOutputDataStream, CCompressOutputStream>());
			continue;
		}
		else if (*arg == "--decompress"s)
		{
			inputWrappers.push(GenerateDecorator<IInputDataStream, CDecompressInputStream>());
			continue;
		}
		PrintUsage(*argv);
		return 1;
	}

	IInputStreamPtr input;
	try
	{
		input = std::make_unique<CFileInputStream>(arg[0]);
	}
	catch (std::ios::failure const&)
	{
		std::cerr << "Failed to open input file\n";
		return 1;
	}
	for (; !inputWrappers.empty(); inputWrappers.pop())
	{
		input = inputWrappers.front()(std::move(input));
	}

	IOutputStreamPtr output;
	try
	{
		output = std::make_unique<CFileOutputStream>(arg[1]);
	}
	catch (std::ios::failure const&)
	{
		std::cerr << "Failed to open output file\n";
		return 1;
	}
	for (; !outputWrappers.empty(); outputWrappers.pop())
	{
		output = outputWrappers.top()(std::move(output));
	}

	try
	{
		uint8_t block[4096];
		while (auto size = input->ReadBlock(block, sizeof block))
		{
			output->WriteBlock(block, size);
		}
	}
	catch (std::ios::failure const&)
	{
		std::cerr << "Failed to perform conversion\n";
		return 1;
	}
	return 0;
}
