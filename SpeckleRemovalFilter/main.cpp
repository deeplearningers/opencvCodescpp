
/**
* Takes a 2d array of grey level values and applies the
* Crimmins Speckle Reduction algorithm to it for a
* specified number of iterations.
*
* @param image the input image
* @param width of the input image
* @param height of the input image
* @param iterations to be applied
* @return the new Crimminsed image
*/
public int[][] crimminsImage(int[][] image, int width,int height, int iterations){
	int[][] image2 = (int[][]) image.clone();
	for (int its = 0; its<iterations; ++its){
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && image[i - 1][j]>image[i][j] + 1){
					image2[i][j] = image[i][j] + 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && i + 1<width
					&& image2[i - 1][j]>image2[i][j] && image2[i + 1][j] >= image2[i][j]){
					image[i][j] = image2[i][j] + 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i + 1<width && i - 1 >= 0
					&& image[i - 1][j] >= image[i][j] && image[i + 1][j]>image[i][j]){
					image2[i][j] = image[i][j] + 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i + 1<width && image2[i + 1][j]>image2[i][j] + 1){
					image[i][j] = image2[i][j] + 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && image[i - 1][j]<image[i][j] - 1){
					image2[i][j] = image[i][j] - 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && i + 1<width
					&& image2[i - 1][j]<image2[i][j] && image2[i + 1][j] <= image2[i][j]){
					image[i][j] = image2[i][j] - 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i + 1<width && i - 1 >= 0
					&& image[i - 1][j] <= image[i][j] && image[i + 1][j]<image[i][j]){
					image2[i][j] = image[i][j] - 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i + 1<width && image2[i + 1][j]<image2[i][j] - 1){
					image[i][j] = image2[i][j] - 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (j - 1 >= 0 && image[i][j - 1]>image[i][j] + 1){
					image2[i][j] = image[i][j] + 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (j - 1 >= 0 && j + 1<height
					&& image2[i][j - 1]>image2[i][j] && image2[i][j + 1] >= image2[i][j]){
					image[i][j] = image2[i][j] + 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (j + 1<height && j - 1 >= 0
					&& image[i][j - 1] >= image[i][j] && image[i][j + 1]>image[i][j]){
					image2[i][j] = image[i][j] + 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (j + 1<height && image2[i][j + 1]>image2[i][j] + 1){
					image[i][j] = image2[i][j] + 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (j - 1 >= 0 && image[i][j - 1]<image[i][j] - 1){
					image2[i][j] = image[i][j] - 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (j - 1 >= 0 && j + 1<height
					&& image2[i][j - 1]<image2[i][j] && image2[i][j + 1] <= image2[i][j]){
					image[i][j] = image2[i][j] - 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (j + 1<height && j - 1 >= 0
					&& image[i][j - 1] <= image[i][j] && image[i][j + 1]<image[i][j]){
					image2[i][j] = image[i][j] - 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (j + 1<height && image2[i][j + 1]<image2[i][j] - 1){
					image[i][j] = image2[i][j] - 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i + 1<width && j - 1 >= 0
					&& image[i + 1][j - 1]>image[i][j] + 1){
					image2[i][j] = image[i][j] + 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && i + 1<width && j - 1 >= 0 && j + 1<height
					&& image2[i + 1][j - 1]>image2[i][j]
					&& image2[i - 1][j + 1] >= image2[i][j]){
					image[i][j] = image2[i][j] + 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && i + 1<width && j - 1 >= 0 && j + 1<height
					&& image[i + 1][j - 1] >= image[i][j]
					&& image[i - 1][j + 1]>image[i][j]){
					image2[i][j] = image[i][j] + 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && j + 1<height
					&& image2[i - 1][j + 1]>image2[i][j] + 1){
					image[i][j] = image2[i][j] + 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i + 1<width && j - 1 >= 0
					&& image[i + 1][j - 1]<image[i][j] - 1){
					image2[i][j] = image[i][j] - 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && i + 1<width && j - 1 >= 0 && j + 1<height
					&& image2[i + 1][j - 1]<image2[i][j]
					&& image2[i - 1][j + 1] <= image2[i][j]){
					image[i][j] = image2[i][j] - 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && i + 1<width && j - 1 >= 0 && j + 1<height
					&& image[i + 1][j - 1] <= image[i][j]
					&& image[i - 1][j + 1]<image[i][j]){
					image2[i][j] = image[i][j] - 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && j + 1<height
					&& image2[i - 1][j + 1]<image2[i][j] - 1){
					image[i][j] = image2[i][j] - 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i + 1<width && j + 1<height
					&& image[i + 1][j + 1]>image[i][j] + 1){
					image2[i][j] = image[i][j] + 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && i + 1<width && j - 1 >= 0 && j + 1<height
					&& image2[i + 1][j + 1]>image2[i][j]
					&& image2[i - 1][j - 1] >= image2[i][j]){
					image[i][j] = image2[i][j] + 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && i + 1<width && j - 1 >= 0 && j + 1<height
					&& image[i + 1][j + 1] >= image[i][j]
					&& image[i - 1][j - 1]>image[i][j]){
					image2[i][j] = image[i][j] + 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && j - 1 >= 0
					&& image2[i - 1][j - 1]>image2[i][j] + 1){
					image[i][j] = image2[i][j] + 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i + 1<width && j + 1<height
					&& image[i + 1][j + 1]<image[i][j] - 1){
					image2[i][j] = image[i][j] - 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && i + 1<width && j - 1 >= 0 && j + 1<height
					&& image2[i + 1][j + 1]<image2[i][j]
					&& image2[i - 1][j - 1] <= image2[i][j]){
					image[i][j] = image2[i][j] - 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && i + 1<width && j - 1 >= 0 && j + 1<height
					&& image[i + 1][j + 1] <= image[i][j]
					&& image[i - 1][j - 1]<image[i][j]){
					image2[i][j] = image[i][j] - 1;
				}
				else image2[i][j] = image[i][j];
			}
		}
		for (int j = 0; j<height; ++j){
			for (int i = 0; i<width; ++i){
				if (i - 1 >= 0 && j - 1 >= 0
					&& image2[i - 1][j - 1]<image2[i][j] - 1){
					image[i][j] = image2[i][j] - 1;
				}
				else image[i][j] = image2[i][j];
			}
		}
	}
	return image;
}




/**
* Takes a 2d image and applies Crimmins to it.
*
* @param input the input image
* @param width of the input image
* @param height of the input image
* @param iterations to be applied
* @return the new image
*/
public int[][] crimmins(int[][] input, int width, int height,int iterations){
	int[][] output = new int[width][height];
	for (int j = 0; j<height; ++j){
		for (int i = 0; i<width; ++i){
			input[i][j] = (new Color(input[i][j])).getRed();
		}
	}
	output = crimminsImage(input, width, height, iterations);
	return output;
}