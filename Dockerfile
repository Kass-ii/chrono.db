# Use an official lightweight image that includes the GCC compiler
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /app

# Copy your C source code from your computer into the container
COPY . .

# Run the compiler to build your executable file, naming it "mydb"
RUN gcc -o mydb *.c

# Set the default command to run when the container starts
CMD ["./mydb"]