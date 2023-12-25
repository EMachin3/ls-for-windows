#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
namespace fs = std::filesystem;
int main()
{
	auto path = fs::current_path();
	std::string longest_filename;
	std::vector<std::string> filenames_list;
	int longest_filename_index = -1;
	int i = 0;
	for (const auto& entry : fs::directory_iterator(path)) {
		auto file = entry.path().filename();
		std::string filename = file.string();
		if (fs::is_directory(file)) {
			std::string temp = "\x1B[34m";
			temp.append(filename);
			temp.append("\033[0m");
			filename = temp;
		}
		if (filename.size() > longest_filename.size()) {
			longest_filename = filename; 
			longest_filename_index = i;
		}
		filenames_list.push_back(filename);
		i++;
	}
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int window_columns = csbi.srWindow.Right - csbi.srWindow.Left + 1 - 20; //subtract 20 to add space on the right
	int output_columns = (window_columns) / longest_filename.size();
	if (output_columns > 5) { output_columns = 5; } //linux ls is limited to 5 columns (for good reason)
	else if (output_columns < 1) { output_columns = 1; }
	int amount_padding = longest_filename.size() + 3;
	std::vector<std::vector<std::string>> sublists;
	int min_filenames_per_sublist = filenames_list.size() / output_columns;
	int leftover_filenames = filenames_list.size() % output_columns;
	//add columns with minimum number of filenames
	for (int i = 1; i < output_columns - leftover_filenames + 1; i++)
	{
		sublists.insert(sublists.begin(), std::vector<std::string>(filenames_list.end() - i * min_filenames_per_sublist, filenames_list.end() - (i - 1) * min_filenames_per_sublist));
	}
	//add columns with 1 more filename than minimum
	for (int i = 1; i < leftover_filenames + 1; i++)
	{
		sublists.insert(sublists.end() - (output_columns - leftover_filenames), std::vector<std::string>(filenames_list.begin() + (i - 1) * (min_filenames_per_sublist + 1), filenames_list.begin() + i * (min_filenames_per_sublist + 1)));
	}
	for (int i = 0; i < min_filenames_per_sublist; i++)
	{
		for (int j = 0; j < output_columns; j++)
		{
			if (sublists[j][i][0] == '\x1B') //if colored text
			{
				std::cout << std::setw(amount_padding + 9) << std::left << sublists[j][i];
			}
			else
			{
				std::cout << std::setw(amount_padding) << std::left << sublists[j][i];
			}
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < leftover_filenames; i++)
	{
		std::cout << std::setw(amount_padding) << sublists[i][min_filenames_per_sublist];
	}
	std::cout << std::endl;
	return 0;
}